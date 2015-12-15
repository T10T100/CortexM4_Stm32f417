
#ifndef TFT_H
#define TFT_H


/*============================================================================*/
/*                               ***ILI9488***                                */
/*                        TFT LCD Single Chip Driver                          */
/*                        Command List Specifications                         */
/*============================================================================*/

/*Note: Following text and descriptions are partially copied from the original*/
/*product datasheet and for detail information  please refer to the manufacrer*/
/*Web-Site.                                                                   */
/*===========================Stansart Command list============================*/

union __IntToByte {
	uint8_t Byte[2];
	uint16_t Int;
};

enum LcdCmdEnumDef {
    LcdCmdNop       = 0x00,
    LcdCmdSWRESET   = 0x01,
    LcdCmdRDDIDIF   = 0x04,
    LcdCmdRDNUMED   = 0x05,
    LcdCmdRDDST     = 0x09,
    LcdCmdRDDPM     = 0x0A,
    LcdCmdRDDMADCTL = 0x0B,
    LcdCmdRDDCOLMOD = 0x0C,
    LcdCmdRDDIM     = 0x0D,
    LcdCmdRDDSM     = 0x0E,
    LcdCmdRDDSDR    = 0x0F,
    LcdCmdSLPOUT    = 0x11,
    LcdCmdPTLON     = 0x12,
    LcdCmdNORON     = 0x13,
    LcdCmdINVOFF    = 0x20,
    LcdCmdINVON     = 0x21,
    LcdCmdALLPOFF   = 0x22,
    LcdCmdALLPON    = 0x23,
    LcdCmdDISOFF    = 0x28,
    LcdCmdDISON     = 0x29,
    LcdCmdCASET     = 0x2A,
    LcdCmdPASET     = 0x2B,
    LcdCmdRAMWR     = 0x2C,
    LcdCmdRAMRD     = 0x2E,
    LcdCmdPLTAR     = 0x30,
    LcdCmdVSCRDEF   = 0x33,
    LcdCmdTEOFF     = 0x34,
    LcdCmdTEON      = 0x35,
    LcdCmdMADCTL    = 0x36,
    LcdCmdVSCRSADD  = 0x37,
    LcdCmdIDMOFF    = 0x38,
    LcdCmdIDMON     = 0x39,
    LcdCmdCOLMOD    = 0x3A,
    LcdCmdRAMWRC    = 0x3C,
    LcdCmdRAMRDRC   = 0x3E,
    LcdCmdTESLWR    = 0x44,
    LcdCmdWRDISBV   = 0x51,
    LcdCmdRDDISBV   = 0x52,
    LcdCmdWRCTRLD   = 0x53,
    LcdCmdRDCTRLD   = 0x54,
    LcdCmdWRCABC    = 0x55,
    LcdCmdRDCABC    = 0x56,
    LcdCmdWRCABCMB  = 0x5E,
    LcdCmdRDCABCMB  = 0x5F,
    LcdCmdRDABCSDR  = 0x68,
    LcdCmdRDID1     = 0xDA,
    LcdCmdRDID2     = 0xDB,
    LcdCmdRDID3     = 0xDC,
};

enum LcdExCmdEnumDef {
    LcdCmdIFMODE                = 0xB0,
    LcdCmdFRMCTR1               = 0xB1,
    LcdCmdFRMCTR2               = 0xB2,
    LcdCmdFRMCTR3               = 0xB3,
    LcdCmdINVTR                 = 0xB4,
    LcdCmdPRCTR                 = 0xB5,
    LcdCmdDISCTRL               = 0xB6,
    LcdCmdETMOD                 = 0xB7,
    LcdCmdCECTRL1               = 0xB9,
    LcdCmdCECTRL2               = 0xBA,
    LcdCmdHSLCTRL               = 0xBE,
    LcdCmdPWCTRL1               = 0xC0,
    LcdCmdPWCTRL2               = 0xC1,
    LcdCmdPWCTRL3               = 0xC2,
    LcdCmdPWCTRL4               = 0xC3,
    LcdCmdPWCTRL5               = 0xC4,
    LcdCmdVMCTRL                = 0xC5,
    LcdCmdCABCCTRL1             = 0xC6,
    LcdCmdCABCCTRL2             = 0xC8,
    LcdCmdCABCCTRL3             = 0xC9,
    LcdCmdCABCCTRL4             = 0xCA,
    LcdCmdCABCCTRL5             = 0xCB,
    LcdCmdCABCCTRL6             = 0xCC,
    LcdCmdCABCCTRL7             = 0xCD,
    LcdCmdCABCCTRL8             = 0xCE,
    LcdCmdCABCCTRL9             = 0xCF,
    LcdCmdNVMWR                 = 0xD0,
    LcdCmdNVMPKEY               = 0xD1,
    LcdCmdNVMSR                 = 0xD2,
    LcdCmdRDID4                 = 0xD3,
    LcdCmdAdjustControl1        = 0xD7,
    LcdCmdPGAMCTRL              = 0xE0,
    LcdCmdNGAMCTRL              = 0xE1,
    LcdCmdDGAMCTRL              = 0xE2,
    LcdCmdDGAMCTRL2             = 0xE3,
    LcdCmdSETIMAGE              = 0xE9,
    LcdCmdAdjustControl2        = 0xF2,
    LcdCmdAdjustControl3        = 0xF7,
    LcdCmdAdjustControl4        = 0xF8,
    LcdCmdAdjustControl5        = 0xF9,
    LcdCmdSPIRCS                = 0xFB,
    LcdCmdAdjustControl6        = 0xFC,
};

typedef unsigned short resolution_t; 

#if (1)
/**
  *@Nop(00h)  
  *Has No Parameters
  *This command is an empty command. It does not have any effect on the ILI9488. However, it can be used to terminate Frame
  *Memory Write or Read, as described in RAMWR (Memory Write) and RAMRD (Memory Read) Commands. 
*/

/**@Software @Reset(01h)
  *Has No Parameters
  *When the Software Reset command is written, it causes software reset. It resets commands and parameters to their S/W
  *Reset default values. (See default tables in each command description.)
  *After the Software Reset is applied, the display becomes blank immediately. 
  *
  *It is necessary to wait 5msec before sending a new command after software reset. The display module loads all factory
  *default values of the display supplier to the registers during this 5msec. If Software Reset is applied during the Sleep Out
  *mode, it will be necessary to wait 120msec before sending the Sleep Out command.
  *The Software Reset Command cannot be sent during the Sleep Out sequence.
*/

/**@Read @Display @Identification @Information(04h) 
  *This read byte can read 24 bits of display identification information.
  *The 1st parameter is a dummy data.
  *The 2nd parameter (ID1 [7:0]): LCD module? manufacturer ID
  *The 3rd parameter (ID2 [7:0]): LCD module/driver version ID
  *The 4th parameter (ID3 [7:0]): LCD module/driver ID 
  *
*/

/**@Read @Number @of @the @Errors @on @DSI (05h) 
  *The 1st parameter is a dummy data.
  *The 2nd parameter indicates the number of errors on the DSI. More detailed description of the bits is below.
  *P [6...0] bits indicate the number of the errors.
  *P [7] is set to 1 if there is overflow with P [6..0] bits.
  *P [7...0] bits are set to 0 (RDDSM(0Eh)? D0 is set to 0 at the same time) after the second parameter information is sent (=
  *The read function is completed). This function always returns P [7...0] = 00h if the parallel MCU interface is selected. 
  *
*/

/**@Read @Display @Status (09h)
  *
  *
*/

/**@Read @Display @Power @Mode (0Ah) 
  *
  *
  *
*/

/**@Read @Display @MADCTL (0Bh)  
  *
  *
  *
*/

/**@Read @Display @Pixel @Format (0Ch) 
  *
  *
  *
*/

/**@Read @Display @Image @Mode (0Dh) 
  *
  *
  *
*/

/**@Read @Display @Signal @Mode (0Eh) 
  *
  *
  *
*/

/**@Read @Display @SelfDiagnostic @Result (0Fh) 
  *
  *
  *
*/

/**@Sleep @OUT (11h) 
  *Has no parameters
  *This command turns off the sleep mode.
  *In this mode, the DC/DC converter is enabled, and Internal oscillator and panel scanning are activated. 
  *
  *
*/

/**@Partial @Mode @ON (12h) 
  *Has no parameters
  *This command will turn on the Partial mode. The Partial mode window is described in the Partial Area command (30H).
  *To leave the Partial mode, the Normal Display Mode On command (13H) should be written. 
  *
  *
*/

/**@Normal @Display @Mode @ON (13h)
  *Has no parameters
  *This command will make the display return to the normal mode. Normal Display Mode On means Partial mode off and Scroll
  *mode off.
  *
  *
*/

/**@Display Inversion OFF (20h) 
  *Has no parameters
  *This command is used to recover from the Display Inversion mode. Output from the Frame Memory is enabled.
  *This command makes no change to the content of the frame memory.
  *This command does not change any other status. 
  *
*/

/**@Display @Inversion @ON (21h) 
  *Has no parameters
  *This command is used to enter the Display Inversion mode.
  *This command makes no change of the content of the frame memory. Every bit is inverted from the frame memory to the
  *display.
  *This command does not change any other status.
  *To exit Display Inversion mode, the Display inversion OFF command (20h) should be written. 
*/ 

/**@All @Pixels @   OFF (22h) 
  *Has no parameters
  *This command turns the display panel black in the Sleep Out mode, and the status of the Display On/Off register can be On or
  *Off. This command makes no change to the contents of the Frame Memory. This command does not change any other status.
  *
  *To exit this mode, All Pixels On, Normal Display Mode On or Partial Mode On commands can be used. The display panel
  *shows the content of the Frame Memory after applying Normal Display Mode On and Partial Mode On commands. 
*/

/**@All @Pixels @ON (23h) 
  *Has no parameters
  *This command turns the display panel white in the Sleep Out mode, and the status of the Display On/Off register can be On or
  *Off. This command makes no change to the contents of the Frame Memory. This command does not change any other status.
  *
  *To exit this mode, All Pixels Off, Normal Display Mode On or Partial Mode On commands can be used. The display shows the
  *content of the Frame Memory after applying Normal Display Mode On and Partial Mode On commands. 
*/

/**@Display @OFF (28h) 
  *Has no parameters
  *This command causes the ILI9488 to stop displaying the image data on the display device. The frame memory contents
  *remain unchanged. No status bits are changed. 
*/

/**@Display @ON (29h) 
  *Has no parameters
  *This command causes the ILI9488 to start displaying the image data on the display device. The frame memory contents
  *remain unchanged. No status bits are changed. 
*/

/**@Column @Address @Set (2Ah) 
  *1st Parameter SC [15:8] 
  *2st Parameter SC [7:0] 
  *3st Parameter EC [15:8] 
  *4st Parameter EC [7:0] 
  *This command is used to define the area of the frame memory that the MCU can access. This command makes no change on
  *the other driver status. The values of SC [15:0] and EC [15:0] are referred when RAMWR command is applied. Each value
  *represents one column line in the Frame Memory
*/

/**@Page @Address @Set (2Bh) 
  *1st Parameter SP [15:8] 
  *2st Parameter SP [7:0] 
  *3st Parameter EP [15:8] 
  *4st Parameter EP [7:0] 
  *This command is used to define the area of the frame memory that the MCU can access. This command makes no change on
  *the other driver status. The values of SP [15:0] and EP [15:0] are referred when RAMWR command is applied. Each value
  *represents one Page line in the Frame Memory. 

  *
*/

/**@Memory @Write (2Ch) 
  *Parameters: Pixel Data
  *This command transfers image data from the host processor to the ILI9488? frame memory starting at the pixel location
  *specified by Column Address Set (2Ah) and Page Address Set (2Bh) commands. 
  *
*/ 

/**@Memory @Read (2Eh) 
  *Parameters: Pixel Data
  *This command transfers image data from the ILI9488? frame memory to the host processor starting at the pixel location
  *specified by set_column_address and set_page_address commands. 
  *
*/

/**@Partial @Area (30h) 
  *1st Parameter SR [15:8] 
  *2st Parameter SR [7:0] 
  *3st Parameter ER [15:8] 
  *4st Parameter ER [7:0] 
  *This command defines the Partial Display mode? display area. There are two parameters associated with this command: the
  *first defines the Start Row (SR) and the second the End Row (ER), as illustrated in the following figure. SR and ER refer to the
  *Frame Memory
  *
*/

/**@Vertical @Scrolling @Definition (33h)
  *Has 6 parameters, for detail information see the product datasheet
  *
*/

/**@Tearing @Effect @Line OFF (34h)
  *Has no parameters
  *This command turns off the ILI9488? Tearing Effect output signal on the TE signal line. 
*/

/**@Tearing @Effect @Line @ON (35h) 
  *1st Parameter D0 -> M
  *This command is used to turn ON the Tearing Effect output signal from the TE signal line. Changing the MADCTL bit D4 will
  *not affect this output. The Tearing Effect Line On has one parameter, which describes the mode of the Tearing Effect Output
  *Line. 
*/

/**@Memory @Access @Control (36h) 
  *This command defines read/write scanning direction of the frame memory.
  *This command makes no change on other driver status. 
  *1st Parameter: {
  *D7 MY Row Address Order    -> }
  *D6 MX Column Address Order -> } => These 3 bits control the direction from the MPU to memory write/read.
  *D5 MV Row/Column Exchange  -> }
  *D4 ML Vertical Refresh Order LCD vertical refresh direction control. 
  *D3 BGR RGB-BGR Order
  *D2 MH Horizontal Refresh ORDER LCD horizontal refreshing direction control. 
  *D1 X
  *D0 X
  *
  *
*/

/**@Vertical @Scrolling @Start @Address (37h)  
  *
  *
  *
*/

/**@Idle @Mode @OFF (38h) 
  *
  *
  *
*/

/**@Idle @Mode @ON (39h)  
  *
  *
  *
*/

/**@Interface @Pixel @Format (3Ah) 
  *
  *
  *
*/

/**@Memory @Write @Continue (3Ch)  
  *
  *
  *
*/

/**@Memory @Read @Continue (3Eh) 
  *
  *
  *
*/

/**@Write @Tear @Scan @Line (44h)  
  *
  *
  *
*/

/**@Read @Scan @Line (45h)  
  *
  *
  *
*/

/**@Write @Display @Brightness @Value (51h) 
  *
  *
  *
*/

/**@Read @Display @Brightness @Value (52h)  
  *
  *
  *
*/

/**@Write @CTRL @Display @Value (53h) 
  *
  *
  *
*/

/**@Read @CTRL @Display @Value (54h)  
  *
  *
  *
*/

/**@Write @Content @Adaptive @Brightness @Control @Value (55h)  
  *
  *
  *
*/

/**@Read @Content @Adaptive @Brightness @Control @Value (56h)  
  *
  *
  *
*/

/**@Write @CABC @Minimum @Brightness (5Eh)  
  *
  *
  *
*/

/**@Read @CABC @Minimum @Brightness (5Fh)  
  *
  *
  *
*/

/**@Read @Automatic @Brightness @Control @Selfdiagnostic @Result (68h)  
  *
  *
  *
*/

/**@Read @ID1 (DAh), @Read @ID2 (DBh), @Read @ID3 (DCh)    
  *
  *
  *
*/

/**@ 
  *
  *
  *
*/
#endif
#include <stdint.h>
#include "dimensions.h"
#include "gpio_ex.h"

template <typename RgbPort, typename SpiPort>
class ILI9488 {
    private :
        RgbPort *rgbPort;
        SpiPort *spiPort;
        int colorMask;
        static const uint16_t width = 480;
        static const uint16_t height = 320;
  public:
       uint16_t getW ()
      {
          return width;
      }
       uint16_t getH ()
      {
          return height;
      }
  
    ILI9488 ()
    {
        
    }
    ILI9488                  (
                             RgbPort *rgbPort,  \
                             SpiPort &spiPort,
                             int32_t colorMask)
                             {   
                                this->rgbPort = &rgbPort;
                                this->spiPort = &spiPort;
                                this->colorMask = colorMask;
                             }
    void operator ()         (
                             RgbPort *rgbPort,  \
                             SpiPort &spiPort,
                             int32_t colorMask)
                             {   
                                this->rgbPort = rgbPort;
                                this->spiPort = &spiPort;
                                this->colorMask = colorMask;
                             }
    void Backlight  (uint8_t = 1);

    uint32_t driverFill (uint16_t __color, uint16_t __x = 480, uint16_t __y = 320)
    {
        this->vsClk();
        this->putColor(__color);
        for (int i = __x; i >= 0; i--) {
            for (int t = __y; t > 0; t--) {
                DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
                DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);								
            }
            this->hsClk();
        }
        this->vsClk();
        return 0;
    }
    template <typename VP>
    uint32_t driverFill (uint16_t __color, VP d)
    {
        this->window(d.x, d.y, d.w, d.h);
        this->vsClk();
        this->putColor(__color);
        for (int i = d.w; i >= 0; i--) {
            for (int t = d.h; t > 0; t--) {
                DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
                DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);								
            }
            this->hsClk();
        }
        this->vsClk();
        return 0;
    }
    uint32_t driverFill (uint16_t __color, uint16_t x, uint16_t y, uint16_t w = 480, uint16_t h = 320)
    {
        this->window(x, y, w, h);
        this->putColor(__color);
        for (int i = w; i >= 0; i--) {
            for (int t = h; t > 0; t--) {
                DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
                DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);								
            }
            this->hsClk();
        }
        this->vsClk();
        return 0;
    }
    template <typename Color>
    uint32_t driverFill (Color *colorBuffer, int32_t x, int32_t y, int32_t h, int32_t w, int32_t __scaleX, uint32_t __scaleY)
    { 
        uint32_t Hcnt = 0;
        uint32_t Hscaled = h * __scaleX;
        uint32_t Dcnt = __scaleY; 
        this->window(x, y, w, h);
        for (int i = 0; i < Hscaled; i++) {
            for (int t = 0; t < w; t++) {
                this->rgbOut(colorBuffer[Hcnt +  t]);
                 while (Dcnt--) {
                    DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
                    DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin); 
                 }	  
                Dcnt = __scaleY;
            }
            Hcnt = (i / __scaleX) * w;
            this->hsClk();
        }
        this->vsClk();
        return 0;
    }
    template <typename Color, typename VP>
    uint32_t driverFill (Color *colorBuffer, VP d)
    {
        int32_t W = d.w, H = d.h;
        int32_t S = W * H;
        this->window(d.x, d.y, W, H);
        for (int32_t x = S; x > 0 ; x -= H) { 
            for (uint32_t y = x, H0 = H + x; y < H0; y++) {
                this->rgbOut( colorBuffer[y] );
                DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
                DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);
            }
            this->hsClk();
        }
        this->vsClk();
        return 0;
    }
    template <typename Color, typename FP, typename VP>
    int32_t driverFill (Color *colorBuffer, FP frame, VP p, Color color)
    {

        if (frame.w + p.x < 0 || p.x > frame.w) {
            return -1;
        }
        if (frame.h + p.y < 0 || p.y > frame.h) {
            return -1;
        }
        
        
        
        Box<int> viewBox  = {0, 0, 0, 0};
        Box<int> darkBox0 = {0, 0, 0, 0};
        Box<int> darkBox  = {0, 0, 0, 0};
        int x0, y0, w0, h0;
        int a, b, c, d;
        if (frame.w > width) {
            if (p.x < 0) {
                a = frame.w + p.x;
                if (a > width) {
                    w0 = width;
                    x0 = -p.x;
                    viewBox.x = 0;
                    viewBox.w = width;
                } else {  /*a <= width*/
                    w0 = a;
                    x0 = -p.x;
                    viewBox.x = 0;
                    viewBox.w = w0;
                } 
            } else { /*p.x >= 0 , frame.w > width*/
                    w0 = width - p.x;
                    x0 = 0;
                    viewBox.x = p.x;
                    viewBox.w = width - p.x;
            }
        } else if (frame.w == width) { /**/
            if (p.x < 0) {
                    a = frame.w + p.x;
                    w0 = a;
                    x0 = -p.x;
                    viewBox.x = 0;
                    viewBox.w = w0; 
            } else { /*p.x >= 0, frame.w == width*/
                    w0 = width - p.x;
                    x0 = 0;
                    viewBox.x = p.x;
                    viewBox.w = width - p.x;
                    
            } 
        } else { /*frame.w < width*/
            
        }
        
        
        
        
        if (frame.h > height) {
            if (p.y < 0) {
                a = frame.h + p.y;
                if (a > height) {
                    h0 = height;
                    y0 = -p.y;
                    viewBox.y = 0;
                    viewBox.h = height;
                    if (p.x < 0) {
                        darkBox0.x = w0;
                        darkBox0.w = width - w0;
                        darkBox0.y = 0;
                        darkBox0.h = height;
                        
                    } else {
                        darkBox0.x = 0;
                        darkBox0.w = p.x;
                        darkBox0.y = 0;
                        darkBox0.h = height;
                    }
                    
                } else {  /*a <= height*/
                    h0 = a;
                    y0 = -p.y;
                    viewBox.y = 0;
                    viewBox.h = a;
                    if (p.x < 0) {
                        darkBox0.x = 0;
                        darkBox0.w = w0;
                        darkBox0.y = h0;
                        darkBox0.h = height - h0;
                        
                        darkBox.x = w0;
                        darkBox.w = width - w0;
                        darkBox.y = 0;
                        darkBox.h = height;
                    } else { /*p.x > 0*/
                        darkBox0.x = 0;
                        darkBox0.w = p.x;
                        darkBox0.y = 0;
                        darkBox0.h = height;
                        
                        darkBox.x = p.x;
                        darkBox.w = width - p.x;
                        darkBox.y = h0;
                        darkBox.h = height - h0;
                    }
                } 
            } else { /*p.y >= 0 , frame.h > height*/
                    h0 = height - p.y;
                    y0 = 0;
                    viewBox.y = p.y;
                    viewBox.h = height - p.y;
                    if (p.x < 0) {
                        darkBox0.x = 0;
                        darkBox0.w = w0;
                        darkBox0.y = 0;
                        darkBox0.h = p.y;
                        
                        darkBox.x = w0;
                        darkBox.w = width - w0;
                        darkBox.y = 0;
                        darkBox.h = height;
                    } else { /*p.x >= 0*/
                        darkBox0.x = 0;
                        darkBox0.w = p.x;
                        darkBox0.y = 0;
                        darkBox0.h = height;
                        
                        darkBox.x = p.x;
                        darkBox.w = width - p.x;
                        darkBox.y = 0;
                        darkBox.h = p.y;
                }
                
            }
        } else if (frame.h == height) { /**/
            if (p.y < 0) {
                    a = frame.h + p.y;
                    h0 = a;
                    y0 = -p.y;
                    viewBox.y = 0;
                    viewBox.h = h0;
                
                if (p.x < 0) {
                    darkBox0.x = 0;
                    darkBox0.w = w0;
                    darkBox0.y = h0;
                    darkBox0.h = height - h0;
                    
                    darkBox.x = w0;
                    darkBox.w = width - w0;
                    darkBox.y = 0;
                    darkBox.h = height;
                } else { /*p.x > 0*/
                    darkBox0.x = 0;
                    darkBox0.w = p.x;
                    darkBox0.y = 0;
                    darkBox0.h = height;
                    
                    darkBox.x = p.x;
                    darkBox.w = width - p.x;
                    darkBox.y = h0;
                    darkBox.h = height - h0;
                }
            } else { /*p.y >= 0, frame.h == height*/
                    h0 = height - p.y;
                    y0 = 0;
                    viewBox.y = p.y;
                    viewBox.h = height - p.y;

                if (p.x < 0) {
                    darkBox0.x = 0;
                    darkBox0.w = w0;
                    darkBox0.y = 0;
                    darkBox0.h = p.y;
                    
                    darkBox.x = w0;
                    darkBox.w = width - w0;
                    darkBox.y = 0;
                    darkBox.h = height;
                } else { /*p.x >= 0*/
                    darkBox0.x = 0;
                    darkBox0.w = p.x;
                    darkBox0.y = 0;
                    darkBox0.h = height;
                    
                    darkBox.x = p.x;
                    darkBox.w = width - p.x;
                    darkBox.y = h0;
                    darkBox.h = height - h0;
                }
            } 
        } else { /*frame.h < height*/
            
        }
        this->driverFill(color, darkBox0.x, darkBox0.y, darkBox0.w, darkBox0.h);
        this->driverFill(color, darkBox.x, darkBox.y, darkBox.w, darkBox.h);
        this->window(viewBox.x, viewBox.y, viewBox.w, viewBox.h);
        fillPart(colorBuffer, x0, y0, w0, h0, frame.h);
        return 0;
    }
    
    template <typename Color>
    void fillPart (Color *src, int x, int y, int w, int h, int hF)
    {  
        int x0 = x * hF;
        x = w * hF + x0;
        for (; x0 < x ; x0 += hF) { 
            for (int32_t yi = x0 + y, H = h + x0 + y; yi < H; yi++) {
                DEV_fPort_Out (this->rgbPort, src[yi]);
                //this->rgbOut( colorBuffer[yi] );
                //toggleDot();
                DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
                DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);
            }
            this->hsClk();
        }
    }
    uint16_t init ()
    {
        this->rstHw();
        this->wrCmd8(LcdCmdSWRESET);//Soft Reset
        this->delay(100);
        
        this->wrCmd8(LcdCmdPWCTRL1);//power control
        this->wrData8(0x15);//Vreg1out
        this->wrData8(0x12);//Vreg2out
        
        this->wrCmd8(LcdCmdPWCTRL2);//power control2
        this->wrData8(0x41);//VGH/VGL
        
        this->wrCmd8(LcdCmdVMCTRL);//VCOM Control 1
        this->wrData8(0x00);//nVM
        this->wrData8(0x4A);//VCM_REG [7:0] 
        this->wrData8(0x80);//VCM_REG_EN 
        
        this->wrCmd8(LcdCmdMADCTL);//memory access
        this->wrData8(0x48);//
        
        this->wrCmd8(LcdCmdCOLMOD);//Interface Pixel Format
        this->wrData8(0x50);//
        
        this->wrCmd8(LcdCmdIFMODE);//Interface Mode Control 
        this->wrData8(0x02);//
        
        this->wrCmd8(LcdCmdINVTR);//Display Inversion Control
        this->wrData8(0x00);//
        
        this->wrCmd8(LcdCmdDISCTRL);//RGB/MCU interface
        this->wrData8(0x20);//
        this->wrData8(0x0F);//source/Gate direction
        
        this->wrCmd8(LcdCmdSETIMAGE);//set image function
        this->wrData8(0x00);//disable 24 bit data input
        
        
        
        this->wrCmd8(LcdCmdAdjustControl3);//adjust control
        this->wrData8(0xA9);//
        this->wrData8(0x52);//
        this->wrData8(0x2C);//
        this->wrData8(0x82);//
        
        
        this->delay(100);;
        this->wrCmd8(LcdCmdSLPOUT);//Sleep Out
        this->delay(150);
        this->wrCmd8(LcdCmdDISON);//Display On
        this->delay(15);
        
        return 0;
    }
	uint16_t window (uint16_t __X, uint16_t __Y, uint16_t __dW, uint16_t __dH)
	{
		__IntToByte __TransferA, __TransferB;
		__TransferA.Int = __Y;
		__TransferB.Int = __Y + __dH;
        
		this->wrCmd8(LcdCmdCASET);
		this->wrData8(__TransferA.Byte[1]);
		this->wrData8(__TransferA.Byte[0]);
		this->wrData8(__TransferB.Byte[1]);
		this->wrData8(__TransferB.Byte[0]);
		__TransferA.Int = __X;
		__TransferB.Int = __X + __dW;
		this->wrCmd8(LcdCmdPASET);
		this->wrData8(__TransferA.Byte[1]);
		this->wrData8(__TransferA.Byte[0]);
		this->wrData8(__TransferB.Byte[1]);
		this->wrData8(__TransferB.Byte[0]);
        
        this->dotClk(1);this->vsClk();
		return 0;
	}
  protected:
    void dummyCycle (uint32_t __cnt)
    {
        while (__cnt--);
    }
    uint16_t wrCmd8 (uint8_t __data)
    {
        this->spiPort->send_9bit_Data (0, __data); 
        return 0;
    }
    uint16_t wrData8 (uint8_t __data)
    {
        this->spiPort->send_9bit_Data (1, __data); 
        return 0;
    }
    uint8_t rd8 (void)
    {
        this->wrCmd8( 0xDA);
        return this->spiPort->read_8bit_Data();
    }
    uint16_t rstHw (void)
    {
        this->resetForce(true);
        this->delay(1);
        
        this->resetForce(false);
        this->delay(1);
        
        this->resetForce(true);
        this->delay(150);
        return 0; 
    }   
    void dotClk (uint32_t cnt)
    {
        while (cnt--) {
            DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);
            DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
        }		
    }
    void hsClk (void)
    {
        DEV_Pin_Clr(Lcd_Den_Port, LCD_Den_Pin);
        DEV_Pin_Clr(Lcd_Hsync_Port, LCD_Hsync_Pin);
        this->dotClk(3);
        DEV_Pin_Set(Lcd_Hsync_Port, LCD_Hsync_Pin);
        DEV_Pin_Set(Lcd_Den_Port, LCD_Den_Pin);
    }
    void vsClk (void)
    {
        DEV_Pin_Clr(Lcd_Vsync_Port, LCD_Vsync_Pin); 
        this->hsClk();
        DEV_Pin_Set(Lcd_Vsync_Port, LCD_Vsync_Pin); 
    }
    template <typename Color>
    void putColor (Color color)
    {
        this->rgbOut(color);
    }
    
    
    
    protected:
        
        template <typename Color>
        inline void rgbOut (Color color);
        inline void setVs (bool value);
        inline void setHs(bool value);
        inline void setDot(bool value);
        inline void toggleDot ();
        inline void setDen(bool value);
        inline void resetForce(bool value);
        inline void delay (uint32_t msec);
    public:
        inline void backLight (uint8_t);        
       
}; 



#endif /*TFT_H*/


