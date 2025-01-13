//Copyright (C)2014-2024 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: Template file for instantiation
//Tool Version: V1.9.10.03 Education
//Part Number: GW2A-LV18PG256C8/I7
//Device: GW2A-18
//Device Version: C
//Created Time: Fri Jan 10 18:43:48 2025

//Change the instance name and port connections to the signal names
//--------Copy here to design--------

    Gowin_DPB your_instance_name(
        .douta(douta), //output [31:0] douta
        .doutb(doutb), //output [31:0] doutb
        .clka(clka), //input clka
        .ocea(ocea), //input ocea
        .cea(cea), //input cea
        .reseta(reseta), //input reseta
        .wrea(wrea), //input wrea
        .clkb(clkb), //input clkb
        .oceb(oceb), //input oceb
        .ceb(ceb), //input ceb
        .resetb(resetb), //input resetb
        .wreb(wreb), //input wreb
        .ada(ada), //input [13:0] ada
        .dina(dina), //input [31:0] dina
        .adb(adb), //input [13:0] adb
        .dinb(dinb) //input [31:0] dinb
    );

//--------Copy end-------------------
