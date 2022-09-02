// Copyright 2022 OpenHW Group
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

`ifndef SYNTHESIS
// Task for loading 'mem' with SystemVerilog system task $readmemh()
export "DPI-C" task tb_readHEX;
export "DPI-C" task tb_loadHEX;
export "DPI-C" task init_load;
export "DPI-C" task tb_loadHEXDone;
export "DPI-C" task tb_getMemSize;
export "DPI-C" task tb_set_exit_loop;

import core_v_mini_mcu_pkg::*;

logic [7:0] global_stimuli[core_v_mini_mcu_pkg::MEM_SIZE];
int global_counter, next_global_counter;
logic start_preloading;
logic stop_preloading;
int global_NumBytes;
logic iampreloading;
obi_req_t testobi_req;
obi_resp_t testobi_resp, testobi_resp_q;

task tb_getMemSize;
  output int mem_size;
  mem_size = core_v_mini_mcu_pkg::MEM_SIZE;
endtask

task tb_readHEX;
  input string file;
  output logic [7:0] stimuli[core_v_mini_mcu_pkg::MEM_SIZE];
  $readmemh(file, stimuli);
endtask

task init_load;
  start_preloading = 1'b0;
  stop_preloading  = 1'b0;
endtask  // task

task tb_loadHEX;
  input string file;
  //whether to use debug to write to memories
  int i, j;
  logic [31:0] addr;

  tb_readHEX(file, global_stimuli);
  tb_getMemSize(global_NumBytes);

  start_preloading = 1'b1;
endtask

task tb_loadHEXDone;
  output int done;
  done = stop_preloading == 1'b1;
endtask

task tb_set_exit_loop;
`ifdef VCS
  force core_v_mini_mcu_i.ao_peripheral_subsystem_i.soc_ctrl_i.testbench_set_exit_loop[0] = 1'b1;
  release core_v_mini_mcu_i.ao_peripheral_subsystem_i.soc_ctrl_i.testbench_set_exit_loop[0];
`else
  core_v_mini_mcu_i.ao_peripheral_subsystem_i.soc_ctrl_i.testbench_set_exit_loop[0] = 1'b1;
`endif
endtask

assign stop_preloading = global_counter == global_NumBytes;


typedef enum logic {
  REQ,
  VALID
} preloading_fsm_state;

preloading_fsm_state preloading_state, preloading_nextstate;

always_comb begin
  testobi_resp.gnt = core_v_mini_mcu_i.debug_subsystem_i.dm_obi_top_i.master_gnt_i;
  testobi_resp.rvalid = core_v_mini_mcu_i.debug_subsystem_i.dm_obi_top_i.master_rvalid_i;
  if (iampreloading) begin
    core_v_mini_mcu_i.debug_subsystem_i.dm_obi_top_i.master_req_o = testobi_req.req;
    core_v_mini_mcu_i.debug_subsystem_i.dm_obi_top_i.master_addr_o = testobi_req.addr;
    core_v_mini_mcu_i.debug_subsystem_i.dm_obi_top_i.master_we_o = testobi_req.we;
    core_v_mini_mcu_i.debug_subsystem_i.dm_obi_top_i.master_be_o = testobi_req.be;
    core_v_mini_mcu_i.debug_subsystem_i.dm_obi_top_i.master_wdata_o = testobi_req.wdata;
  end
end


always_comb begin
  testobi_req = '0;
  iampreloading = 1'b0;
  preloading_nextstate = preloading_state;
  next_global_counter = global_counter;

  if (preloading_state == REQ) begin
    if (start_preloading && !stop_preloading) begin
      iampreloading = 1'b1;
      testobi_req.req = 1'b1;
      testobi_req.addr = global_counter;
      testobi_req.we = 1'b1;
      testobi_req.be = 4'b1111;
      testobi_req.wdata = {
        global_stimuli[global_counter+3],
        global_stimuli[global_counter+2],
        global_stimuli[global_counter+1],
        global_stimuli[global_counter]
      };

      if (testobi_resp_q.gnt) preloading_nextstate = VALID;
      else preloading_nextstate = REQ;
    end
  end else if (preloading_state == VALID) begin
    if (testobi_resp_q.rvalid) begin
      preloading_nextstate = REQ;
      next_global_counter  = global_counter + 4;
    end else preloading_nextstate = VALID;
  end
end


always_ff @(negedge core_v_mini_mcu_i.clk_i, negedge core_v_mini_mcu_i.rst_ni) begin
  if (~core_v_mini_mcu_i.rst_ni) begin
    global_counter   <= '0;
    preloading_state <= REQ;
  end else begin
    preloading_state <= preloading_nextstate;
    global_counter   <= next_global_counter;
  end
end

always_ff @(posedge core_v_mini_mcu_i.clk_i, negedge core_v_mini_mcu_i.rst_ni) begin
  if (~core_v_mini_mcu_i.rst_ni) begin
    testobi_resp_q <= '0;
  end else begin
    testobi_resp_q <= testobi_resp;
  end
end

`endif
