--------------------------------------------------------------------------------
ProgICD2 : Standalone PIC programmer for Microchip's ICD2
           Copyright (C) 2007 by altxro (www.altdvb.ro)
--------------------------------------------------------------------------------

Disclaimer:
 Software is provided "as is" without warranty of any kind, express or implied.
 Use it on your own risk. I take no responsibility for any damage or loss caused 
 by using this software.
 
 This software is FREEWARE. You have permission to use, copy, modify and 
 distribute for any purpose and without fee, while copyright notice, credits and 
 disclaimer appear in all copies and supporting documentation.
 
 "ProgICD2" is NOT affiliated with, supported by, or endorsed by Microchip !
  
 "MPLAB","PIC","ICD2" are registered trademarks of Microchip Technology Inc.
 "Windows" is a registered trademark of Microsoft Corporation 

Credits:
 Borland Delphi5   http://www.borland.com
 CoolTrayIcon      http://subsimple.com/delphi.asp
 Virtual Treeview  http://www.soft-gems.net
 Microchip         http://www.microchip.com
 
--------------------------------------------------------------------------------
Installation:
 1) Extract all from archive to your pref. directory.
 
 2) Install Microchip ICD2 USB drivers.
    Search on google/forums if you don't know how to do it.
    (if you already have MPLAB+ICD2 skip this step )
    
 3) Run ProgICD2.exe    

--------------------------------------------------------------------------------
Command line parameters:
 -P <PIC>        ; Microcontroller name (with/without "PIC" or "P" prefix)
 -F <FileName>   ; File to programm ( *.HEX , format INHX8M,INHX16,INHX32)
 -W              ; Command: Write to PIC
 -A              ; Autoload ICD2 firmware without user confirmation
 -Q              ; Close after programming

 
--------------------------------------------------------------------------------
Configurations files:
 * Firmware files must be present in "\Firmware" subdirectory.
   To update, copy ICD????????.hex from latest "...\MPLAB Ide\Icd2\"
   
 * You can add new devices into file "ProgICD2.pic"
   Proper values can be found in microcontroller datasheet and/or
   programming specifications. 
   
   Format:
   ;-
   [16F877A]            ; PIC Name without any literal prefix
   Archt=16X            ; Architecture         ( 10X,16X,17X,18X,30X )
   Firmw=01             ; ICD2 Firmware to use ( see Icd2.xml )
   FamID=04             ; ICD2 family ID       ( see Icd2.xml )
   DevID=0E20           ; Device ID            ( if available )
   MemPG=000000-001FFF  ; MemoryRange: Code
   MemEE=000000-0000FF  ; MemoryRange: Eeprom
   MemCF=002007-002007  ; MemoryRange: Configuration
   MemUI=002000-002003  ; MemoryRange: User ID
   MemDI=002006-002006  ; MemoryRange: Device ID
   MemCA=               ; MemoryRange: Calibration
   ;-
   
--------------------------------------------------------------------------------
Hints:
 * Do not remove USB connector from ICD2 if application is still active
 * If you see "Cannot open driver" error try to restart it (Disable/Enable) from 
   windows Device Manager

--------------------------------------------------------------------------------
Tested on:
 * Operating Systems: Win2K SP4 & WinXP Sp2. I don't know if is working on Vista
 * Microcontrollers : Some PIC16xxx and PIC18xxx (should work for dsPIC30xxx)
   
Download: http://www.altdvb.ro/tools/ProgICD2.zip
   
Happy programming,

[altxro]    
 

  


