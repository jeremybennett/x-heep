// Copyright 2022 EPFL
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

//Works onyl when NumWords = 8192 and so AddrWidth 13
/* verilator lint_off DECLFILENAME */
module sram_wrapper #(
    parameter int unsigned NumWords = 32'd1024,  // Number of Words in data array
    parameter int unsigned DataWidth = 32'd32,  // Data signal width
    // DEPENDENT PARAMETERS, DO NOT OVERWRITE!
    parameter int unsigned AddrWidth = (NumWords > 32'd1) ? $clog2(NumWords) : 32'd1
) (
    input  logic                 clk_i,    // Clock
    input  logic                 rst_ni,   // Asynchronous reset active low
    // input ports
    input  logic                 req_i,    // request
    input  logic                 we_i,     // write enable
    input  logic [AddrWidth-1:0] addr_i,   // request address
    input  logic [         31:0] wdata_i,  // write data
    input  logic [          3:0] be_i,     // write byte enable
    // output ports
    output logic [         31:0] rdata_o   // read data
);

  localparam NumCuts = NumWords/1024;

  logic [NumCuts-1:0] unused;
  logic [NumCuts-1:0] cs;
  logic [NumCuts-1:0][31:0] rdata;
  logic [1:0] data_select_q;

  always_comb
  begin
    cs = '0;
    cs[addr_i[12:11]] = req_i;
  end

  always_ff @(posedge clk_i or negedge rst_ni) begin : proc_data_select_q
    if(~rst_ni) begin
       data_select_q <= 0;
    end else begin
       data_select_q <= req_i ? addr_i[12:11] : data_select_q;
    end
  end

  assign rdata_o = rdata[data_select_q][31:0];

  genvar i;
  generate
    for(i=0; i<NumCuts;i=i++) begin
        sky130_sram_4kbyte_1rw_32x1024_8 #(
          .DELAY(0),
          .VERBOSE(0),
          .T_HOLD(0)
        ) sky130_ram_i (
          .clk0(clk_i),
          .csb0(~cs[i]),
          .web0(~we_i),
          .wmask0(be_i),
          .spare_wen0(1'b0),
          .addr0(addr_i[10:0]),
          .din0({1'b0, wdata_i}),
          .dout0({unused[i], rdata[i]})
        );
    end
  endgenerate



endmodule
