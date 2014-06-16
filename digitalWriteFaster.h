/****************************************************************************** 
*                            digitalWriteFaster.h  
*
*  An ultra-fast hardware specific replacement for both 
*  digitalWrite and digitalRead.
*
*  Works for Maple, Maple-Mini, Maple Native, and Maple Ret6.
*
*  To use, create a folder named 'digitalWriteFaster' inside your 'libraries' folder.  
*  Create a text file named 'digitalWriteFaster.h' and cut&paste this code.
*
*  Use 'digitalWriteFaster' and 'digitalReadFaster' in the original manner.
*
*  Based on code written by moderator 'gbulmer' and member 'manitou'.  
*  Re-packaged by member tlgosser 4/24/2013.
*  http://forums.leaflabs.com/topic.php?id=737
*
*****************************************************************************/

#ifndef _DIGITALWRITEFASTER_H_
#define _DIGITALWRITEFASTER_H_


#include "gpio.h"
#include "adc.h"
#include "wirish_time.h"

typedef unsigned int uint32_t;

#define ODR (0x0C>>2)  // offset of output register within port
#define IDR (0x08>>2)  // offset of input register within port

// Address of output data register for each GPIO peripheral
#define GPIOA_ODR ((uint32_t*) GPIOA_BASE+ODR)
#define GPIOB_ODR ((uint32_t*) GPIOB_BASE+ODR)
#define GPIOC_ODR ((uint32_t*) GPIOC_BASE+ODR)
#define GPIOD_ODR ((uint32_t*) GPIOD_BASE+ODR)
#define GPIOE_ODR ((uint32_t*) GPIOE_BASE+ODR)
#define GPIOF_ODR ((uint32_t*) GPIOF_BASE+ODR)
#define GPIOG_ODR ((uint32_t*) GPIOG_BASE+ODR)

#define GPIOA_IDR ((uint32_t*) GPIOA_BASE+IDR)
#define GPIOB_IDR ((uint32_t*) GPIOB_BASE+IDR)
#define GPIOC_IDR ((uint32_t*) GPIOC_BASE+IDR)
#define GPIOD_IDR ((uint32_t*) GPIOD_BASE+IDR)
#define GPIOE_IDR ((uint32_t*) GPIOE_BASE+IDR)
#define GPIOF_IDR ((uint32_t*) GPIOF_BASE+IDR)
#define GPIOG_IDR ((uint32_t*) GPIOG_BASE+IDR)

// Formula converts peripheral address to bit band peripheral address
// See ARMs Cortex™-M3 Technical Reference Manual for details
// Must all be calculated at compile time
#define BB_PERIPHERAL(peripheral_address, bit) ((volatile uint32_t*)  (0x42000000 \
        + ((uint32_t)peripheral_address - 0x40000000) * 32 + bit * 4))
                
       
#ifdef BOARD_maple_mini
    // uses http://leaflabs.com/docs/hardware/maple-mini.html#gpio-port-pin-map
    // to map Maple mini pins back to STM32F103CB
    // Each entry is the bit-band address of one GPIO output pin
  volatile uint32_t* const bb_port_ODR_bit_address[] = {
        BB_PERIPHERAL(GPIOB_ODR, 11),          // D0
        BB_PERIPHERAL(GPIOB_ODR, 10),          // D1
        BB_PERIPHERAL(GPIOB_ODR,  2),          // D2
        BB_PERIPHERAL(GPIOB_ODR,  0),          // D3
        BB_PERIPHERAL(GPIOA_ODR,  7),          // D4
        BB_PERIPHERAL(GPIOA_ODR,  6),          // D5
        BB_PERIPHERAL(GPIOA_ODR,  5),          // D6
        BB_PERIPHERAL(GPIOA_ODR,  4),          // D7
        BB_PERIPHERAL(GPIOA_ODR,  3),          // D8
        BB_PERIPHERAL(GPIOA_ODR,  2),          // D9
        BB_PERIPHERAL(GPIOA_ODR,  1),          // D10
        BB_PERIPHERAL(GPIOA_ODR,  0),          // D11
        BB_PERIPHERAL(GPIOC_ODR, 15),          // D12
        BB_PERIPHERAL(GPIOC_ODR, 14),          // D13
        BB_PERIPHERAL(GPIOC_ODR, 13),          // D14
        BB_PERIPHERAL(GPIOB_ODR,  7),           //D15
        BB_PERIPHERAL(GPIOB_ODR,  6),           //D16
        BB_PERIPHERAL(GPIOB_ODR,  5),           //D17
        BB_PERIPHERAL(GPIOB_ODR,  4),           //D18
        BB_PERIPHERAL(GPIOB_ODR,  3),           //D19
        BB_PERIPHERAL(GPIOA_ODR,  15),          //D20
        BB_PERIPHERAL(GPIOA_ODR,  14),          //D21
        BB_PERIPHERAL(GPIOA_ODR,  13),          //D22
        BB_PERIPHERAL(GPIOA_ODR,  12),          //D23
        BB_PERIPHERAL(GPIOA_ODR,  11),          //D24
        BB_PERIPHERAL(GPIOA_ODR,  10),          //D25
        BB_PERIPHERAL(GPIOA_ODR,  9),           //D26
        BB_PERIPHERAL(GPIOA_ODR,  8),           //D27
        BB_PERIPHERAL(GPIOB_ODR,  15),          //D28
        BB_PERIPHERAL(GPIOB_ODR,  14),          //D29
        BB_PERIPHERAL(GPIOB_ODR,  13),          //D30
        BB_PERIPHERAL(GPIOB_ODR,  12)           //D31
    };
    
    // Each entry is the bit-band address of one GPIO input pin
    volatile uint32_t* const bb_port_IDR_bit_address[] = {
        BB_PERIPHERAL(GPIOB_IDR, 11),          // D0
        BB_PERIPHERAL(GPIOB_IDR, 10),          // D1
        BB_PERIPHERAL(GPIOB_IDR,  2),          // D2
        BB_PERIPHERAL(GPIOB_IDR,  0),          // D3
        BB_PERIPHERAL(GPIOA_IDR,  7),          // D4
        BB_PERIPHERAL(GPIOA_IDR,  6),          // D5
        BB_PERIPHERAL(GPIOA_IDR,  5),          // D6
        BB_PERIPHERAL(GPIOA_IDR,  4),          // D7
        BB_PERIPHERAL(GPIOA_IDR,  3),          // D8
        BB_PERIPHERAL(GPIOA_IDR,  2),          // D9
        BB_PERIPHERAL(GPIOA_IDR,  1),          // D10
        BB_PERIPHERAL(GPIOA_IDR,  0),          // D11
        BB_PERIPHERAL(GPIOC_IDR, 15),          // D12
        BB_PERIPHERAL(GPIOC_IDR, 14),          // D13
        BB_PERIPHERAL(GPIOC_IDR, 13),          // D14
        BB_PERIPHERAL(GPIOB_IDR,  7),          // D15
        BB_PERIPHERAL(GPIOB_IDR,  6),          // D16
        BB_PERIPHERAL(GPIOB_IDR,  5),          // D17
        BB_PERIPHERAL(GPIOB_IDR,  4),          // D18
        BB_PERIPHERAL(GPIOB_IDR,  3),          // D19
        BB_PERIPHERAL(GPIOA_IDR,  15),         // D20
        BB_PERIPHERAL(GPIOA_IDR,  14),         // D21
        BB_PERIPHERAL(GPIOA_IDR,  13),         // D22
        BB_PERIPHERAL(GPIOA_IDR,  12),         // D23
        BB_PERIPHERAL(GPIOA_IDR,  11),         // D24
        BB_PERIPHERAL(GPIOA_IDR,  10),         // D25
        BB_PERIPHERAL(GPIOA_IDR,  9),          // D26
        BB_PERIPHERAL(GPIOA_IDR,  8),          // D27
        BB_PERIPHERAL(GPIOB_IDR,  15),         // D28
        BB_PERIPHERAL(GPIOB_IDR,  14),         // D29
        BB_PERIPHERAL(GPIOB_IDR,  13),         // D30
        BB_PERIPHERAL(GPIOB_IDR,  12)          // D31
    };
  

#elif defined  BOARD_maple_native
    // uses http://leaflabs.com/docs/hardware/maple-native-beta.html#gpio-port-pin-map
    volatile uint32_t* const bb_port_ODR_bit_address[] = {      
        BB_PERIPHERAL(GPIOB_ODR,  10),          // D0   
        BB_PERIPHERAL(GPIOB_ODR,  11),          // D1 	
        BB_PERIPHERAL(GPIOB_ODR,  12),          // D2 	        
        BB_PERIPHERAL(GPIOB_ODR,  13),          // D3 	
        BB_PERIPHERAL(GPIOB_ODR,  14),          // D4 
        BB_PERIPHERAL(GPIOB_ODR,  15),          // D5                 
        BB_PERIPHERAL(GPIOG_ODR,  15),          // D6 button pin         
        BB_PERIPHERAL(GPIOC_ODR,  0),           // D7 	
        BB_PERIPHERAL(GPIOC_ODR,  1),           // D8 	
        BB_PERIPHERAL(GPIOC_ODR,  2),           // D9 	
        BB_PERIPHERAL(GPIOC_ODR,  3),           // D10 	        
        BB_PERIPHERAL(GPIOC_ODR,  4),           // D11 	
        BB_PERIPHERAL(GPIOC_ODR,  5),           // D12 	
        BB_PERIPHERAL(GPIOC_ODR,  6),           // D13 	
        BB_PERIPHERAL(GPIOC_ODR,  7),           // D14 	
        BB_PERIPHERAL(GPIOC_ODR,  8),           // D15 	
        BB_PERIPHERAL(GPIOC_ODR,  9),           // D16 	
        BB_PERIPHERAL(GPIOC_ODR,  10),          // D17 	
        BB_PERIPHERAL(GPIOC_ODR,  11),          // D18 	
        BB_PERIPHERAL(GPIOC_ODR,  12),          // D19 	
        BB_PERIPHERAL(GPIOC_ODR,  13),          // D20 	        
        BB_PERIPHERAL(GPIOC_ODR,  14),          // D21 	   
        BB_PERIPHERAL(GPIOC_ODR,  15),          // D22                          
        BB_PERIPHERAL(GPIOA_ODR,  8),           // D23 	
        BB_PERIPHERAL(GPIOA_ODR,  9),           // D24 	
        BB_PERIPHERAL(GPIOA_ODR,  10),          // D25 	
        BB_PERIPHERAL(GPIOB_ODR,  9),           // D26 	
        BB_PERIPHERAL(GPIOD_ODR,  2),           // D27
        BB_PERIPHERAL(GPIOD_ODR,  3),           // D28        
        BB_PERIPHERAL(GPIOD_ODR,  6),           // D29
        BB_PERIPHERAL(GPIOG_ODR,  11),          // D30
        BB_PERIPHERAL(GPIOG_ODR,  12),          // D31        
        BB_PERIPHERAL(GPIOG_ODR,  13),          // D32
        BB_PERIPHERAL(GPIOG_ODR,  14)           // D33      
        BB_PERIPHERAL(GPIOG_ODR,  8),           // D34
        BB_PERIPHERAL(GPIOG_ODR,  7),           // D35        
        BB_PERIPHERAL(GPIOG_ODR,  6),           // D36        
        BB_PERIPHERAL(GPIOB_ODR,  5),           // D37 	        
        BB_PERIPHERAL(GPIOB_ODR,  6),           // D38 	
        BB_PERIPHERAL(GPIOB_ODR,  7),           // D39 	
        BB_PERIPHERAL(GPIOF_ODR,  11),          // D40 	
        BB_PERIPHERAL(GPIOF_ODR,  6),           // D41 	        
        BB_PERIPHERAL(GPIOF_ODR,  7),           // D42 	
        BB_PERIPHERAL(GPIOF_ODR,  8),           // D43 	
        BB_PERIPHERAL(GPIOF_ODR,  9),           // D44 	
        BB_PERIPHERAL(GPIOF_ODR,  10),          // D45 	        
        BB_PERIPHERAL(GPIOB_ODR,  1),           // D46 	        
        BB_PERIPHERAL(GPIOB_ODR,  0),           // D47 	
        BB_PERIPHERAL(GPIOA_ODR,  0),           // D48 
        BB_PERIPHERAL(GPIOA_ODR,  1),           // D49 	        
        BB_PERIPHERAL(GPIOA_ODR,  2),           // D50 
        BB_PERIPHERAL(GPIOA_ODR,  3),           // D51 	        
        BB_PERIPHERAL(GPIOA_ODR,  4),           // D52 	
        BB_PERIPHERAL(GPIOA_ODR,  5),           // D53 	
        BB_PERIPHERAL(GPIOA_ODR,  6),           // D54 	
        BB_PERIPHERAL(GPIOA_ODR,  7),           // D55 	        
        BB_PERIPHERAL(GPIOF_ODR,  0),           // D56 
        BB_PERIPHERAL(GPIOD_ODR,  11),          // D57        
        BB_PERIPHERAL(GPIOD_ODR,  14),          // D58              
        BB_PERIPHERAL(GPIOF_ODR,  1),           // D59 	        
        BB_PERIPHERAL(GPIOD_ODR,  12),          // D60
        BB_PERIPHERAL(GPIOD_ODR,  15),          // D61                          
        BB_PERIPHERAL(GPIOF_ODR,  2),           // D62 
        BB_PERIPHERAL(GPIOD_ODR,  13),          // D63        	        	        	        
        BB_PERIPHERAL(GPIOD_ODR,  0),           // D64
        BB_PERIPHERAL(GPIOF_ODR,  3),           // D65
        BB_PERIPHERAL(GPIOE_ODR,  3),           // D66 	
        BB_PERIPHERAL(GPIOD_ODR,  1),           // D67
        BB_PERIPHERAL(GPIOF_ODR,  4),           // D68 	
        BB_PERIPHERAL(GPIOE_ODR,  4),           // D69 	
        BB_PERIPHERAL(GPIOE_ODR,  7),           // D70 	 	
        BB_PERIPHERAL(GPIOF_ODR,  5),           // D71
        BB_PERIPHERAL(GPIOE_ODR,  5),           // D72        
        BB_PERIPHERAL(GPIOE_ODR,  8),           // D73 	
        BB_PERIPHERAL(GPIOF_ODR,  12),          // D74 	
        BB_PERIPHERAL(GPIOE_ODR,  6),           // D75 	
        BB_PERIPHERAL(GPIOE_ODR,  9),           // D76 	        
        BB_PERIPHERAL(GPIOF_ODR,  13),          // D77 	
        BB_PERIPHERAL(GPIOE_ODR,  10),          // D78 	        
        BB_PERIPHERAL(GPIOF_ODR,  14),          // D79 	
        BB_PERIPHERAL(GPIOG_ODR,  9),           // D80
        BB_PERIPHERAL(GPIOE_ODR,  11),          // D81 
        BB_PERIPHERAL(GPIOF_ODR,  15),          // D82                                  	
        BB_PERIPHERAL(GPIOG_ODR,  10),          // D83
        BB_PERIPHERAL(GPIOE_ODR,  12),          // D84 
        BB_PERIPHERAL(GPIOG_ODR,  0),           // D85        
        BB_PERIPHERAL(GPIOD_ODR,  5),           // D86
        BB_PERIPHERAL(GPIOE_ODR,  13),          // D87 	
        BB_PERIPHERAL(GPIOG_ODR,  1),           // D88
        BB_PERIPHERAL(GPIOD_ODR,  4),           // D89
        BB_PERIPHERAL(GPIOE_ODR,  14),          // D90 	        
        BB_PERIPHERAL(GPIOG_ODR,  2),           // D91 	         
        BB_PERIPHERAL(GPIOE_ODR,  1),           // D92 	
        BB_PERIPHERAL(GPIOE_ODR,  15),          // D93                          
        BB_PERIPHERAL(GPIOG_ODR,  3),           // D94
        BB_PERIPHERAL(GPIOE_ODR,  0),           // D95 	
        BB_PERIPHERAL(GPIOD_ODR,  8),           // D96
        BB_PERIPHERAL(GPIOG_ODR,  4),           // D97        
        BB_PERIPHERAL(GPIOD_ODR,  9),           // D98
        BB_PERIPHERAL(GPIOG_ODR,  5),           // D99
        BB_PERIPHERAL(GPIOD_ODR,  10),          // D100
        BB_PERIPHERAL(GPIOA_ODR,  13),          // D101 	
        BB_PERIPHERAL(GPIOA_ODR,  14),          // D102 
        BB_PERIPHERAL(GPIOA_ODR,  15),          // D103 
        BB_PERIPHERAL(GPIOB_ODR,  3),           // D104 	
        BB_PERIPHERAL(GPIOB_ODR,  4)            // D105 	
    };
    
    // Each entry is the bit-band address of one GPIO input pin
    volatile uint32_t* const bb_port_IDR_bit_address[] = {
        BB_PERIPHERAL(GPIOB_IDR,  10),          // D0 	
        BB_PERIPHERAL(GPIOB_IDR,  11),          // D1 	
        BB_PERIPHERAL(GPIOB_IDR,  12),          // D2 	        
        BB_PERIPHERAL(GPIOB_IDR,  13),          // D3 	
        BB_PERIPHERAL(GPIOB_IDR,  14),          // D4 
        BB_PERIPHERAL(GPIOB_IDR,  15),          // D5                 
        BB_PERIPHERAL(GPIOG_IDR,  15),          // D6 button pin         
        BB_PERIPHERAL(GPIOC_IDR,  0),           // D7 	
        BB_PERIPHERAL(GPIOC_IDR,  1),           // D8 	
        BB_PERIPHERAL(GPIOC_IDR,  2),           // D9 	
        BB_PERIPHERAL(GPIOC_IDR,  3),           // D10 	        
        BB_PERIPHERAL(GPIOC_IDR,  4),           // D11 	
        BB_PERIPHERAL(GPIOC_IDR,  5),           // D12 	
        BB_PERIPHERAL(GPIOC_IDR,  6),           // D13 	
        BB_PERIPHERAL(GPIOC_IDR,  7),           // D14 	
        BB_PERIPHERAL(GPIOC_IDR,  8),           // D15 	
        BB_PERIPHERAL(GPIOC_IDR,  9),           // D16 	
        BB_PERIPHERAL(GPIOC_IDR,  10),          // D17 	
        BB_PERIPHERAL(GPIOC_IDR,  11),          // D18 	
        BB_PERIPHERAL(GPIOC_IDR,  12),          // D19 	
        BB_PERIPHERAL(GPIOC_IDR,  13),          // D20 	        
        BB_PERIPHERAL(GPIOC_IDR,  14),          // D21 	   
        BB_PERIPHERAL(GPIOC_IDR,  15),          // D22                          
        BB_PERIPHERAL(GPIOA_IDR,  8),           // D23 	
        BB_PERIPHERAL(GPIOA_IDR,  9),           // D24 	
        BB_PERIPHERAL(GPIOA_IDR,  10),          // D25 	
        BB_PERIPHERAL(GPIOB_IDR,  9),           // D26 	
        BB_PERIPHERAL(GPIOD_IDR,  2),           // D27
        BB_PERIPHERAL(GPIOD_IDR,  3),           // D28        
        BB_PERIPHERAL(GPIOD_IDR,  6),           // D29
        BB_PERIPHERAL(GPIOG_IDR,  11),          // D30
        BB_PERIPHERAL(GPIOG_IDR,  12),          // D31        
        BB_PERIPHERAL(GPIOG_IDR,  13),          // D32
        BB_PERIPHERAL(GPIOG_IDR,  14)           // D33      
        BB_PERIPHERAL(GPIOG_IDR,  8),           // D34
        BB_PERIPHERAL(GPIOG_IDR,  7),           // D35        
        BB_PERIPHERAL(GPIOG_IDR,  6),           // D36        
        BB_PERIPHERAL(GPIOB_IDR,  5),           // D37 	        
        BB_PERIPHERAL(GPIOB_IDR,  6),           // D38 	
        BB_PERIPHERAL(GPIOB_IDR,  7),           // D39 	
        BB_PERIPHERAL(GPIOF_IDR,  11),          // D40 	
        BB_PERIPHERAL(GPIOF_IDR,  6),           // D41 	        
        BB_PERIPHERAL(GPIOF_IDR,  7),           // D42 	
        BB_PERIPHERAL(GPIOF_IDR,  8),           // D43 	
        BB_PERIPHERAL(GPIOF_IDR,  9),           // D44 	
        BB_PERIPHERAL(GPIOF_IDR,  10),          // D45 	        
        BB_PERIPHERAL(GPIOB_IDR,  1),           // D46 	        
        BB_PERIPHERAL(GPIOB_IDR,  0),           // D47 	
        BB_PERIPHERAL(GPIOA_IDR,  0),           // D48 
        BB_PERIPHERAL(GPIOA_IDR,  1),           // D49 	        
        BB_PERIPHERAL(GPIOA_IDR,  2),           // D50 
        BB_PERIPHERAL(GPIOA_IDR,  3),           // D51 	        
        BB_PERIPHERAL(GPIOA_IDR,  4),           // D52 	
        BB_PERIPHERAL(GPIOA_IDR,  5),           // D53 	
        BB_PERIPHERAL(GPIOA_IDR,  6),           // D54 	
        BB_PERIPHERAL(GPIOA_IDR,  7),           // D55 	        
        BB_PERIPHERAL(GPIOF_IDR,  0),           // D56 
        BB_PERIPHERAL(GPIOD_IDR,  11),          // D57        
        BB_PERIPHERAL(GPIOD_IDR,  14),          // D58              
        BB_PERIPHERAL(GPIOF_IDR,  1),           // D59 	        
        BB_PERIPHERAL(GPIOD_IDR,  12),          // D60
        BB_PERIPHERAL(GPIOD_IDR,  15),          // D61                          
        BB_PERIPHERAL(GPIOF_IDR,  2),           // D62 
        BB_PERIPHERAL(GPIOD_IDR,  13),          // D63        	        	        	        
        BB_PERIPHERAL(GPIOD_IDR,  0),           // D64
        BB_PERIPHERAL(GPIOF_IDR,  3),           // D65
        BB_PERIPHERAL(GPIOE_IDR,  3),           // D66 	
        BB_PERIPHERAL(GPIOD_IDR,  1),           // D67
        BB_PERIPHERAL(GPIOF_IDR,  4),           // D68 	
        BB_PERIPHERAL(GPIOE_IDR,  4),           // D69 	
        BB_PERIPHERAL(GPIOE_IDR,  7),           // D70 	 	
        BB_PERIPHERAL(GPIOF_IDR,  5),           // D71
        BB_PERIPHERAL(GPIOE_IDR,  5),           // D72        
        BB_PERIPHERAL(GPIOE_IDR,  8),           // D73 	
        BB_PERIPHERAL(GPIOF_IDR,  12),          // D74 	
        BB_PERIPHERAL(GPIOE_IDR,  6),           // D75 	
        BB_PERIPHERAL(GPIOE_IDR,  9),           // D76 	        
        BB_PERIPHERAL(GPIOF_IDR,  13),          // D77 	
        BB_PERIPHERAL(GPIOE_IDR,  10),          // D78 	        
        BB_PERIPHERAL(GPIOF_IDR,  14),          // D79 	
        BB_PERIPHERAL(GPIOG_IDR,  9),           // D80
        BB_PERIPHERAL(GPIOE_IDR,  11),          // D81 
        BB_PERIPHERAL(GPIOF_IDR,  15),          // D82                                  	
        BB_PERIPHERAL(GPIOG_IDR,  10),          // D83
        BB_PERIPHERAL(GPIOE_IDR,  12),          // D84 
        BB_PERIPHERAL(GPIOG_IDR,  0),           // D85        
        BB_PERIPHERAL(GPIOD_IDR,  5),           // D86
        BB_PERIPHERAL(GPIOE_IDR,  13),          // D87 	
        BB_PERIPHERAL(GPIOG_IDR,  1),           // D88
        BB_PERIPHERAL(GPIOD_IDR,  4),           // D89
        BB_PERIPHERAL(GPIOE_IDR,  14),          // D90 	        
        BB_PERIPHERAL(GPIOG_IDR,  2),           // D91 	         
        BB_PERIPHERAL(GPIOE_IDR,  1),           // D92 	
        BB_PERIPHERAL(GPIOE_IDR,  15),          // D93                          
        BB_PERIPHERAL(GPIOG_IDR,  3),           // D94
        BB_PERIPHERAL(GPIOE_IDR,  0),           // D95 	
        BB_PERIPHERAL(GPIOD_IDR,  8),           // D96
        BB_PERIPHERAL(GPIOG_IDR,  4),           // D97        
        BB_PERIPHERAL(GPIOD_IDR,  9),           // D98
        BB_PERIPHERAL(GPIOG_IDR,  5),           // D99
        BB_PERIPHERAL(GPIOD_IDR,  10),          // D100
        BB_PERIPHERAL(GPIOA_IDR,  13),          // D101 	
        BB_PERIPHERAL(GPIOA_IDR,  14),          // D102 
        BB_PERIPHERAL(GPIOA_IDR,  15),          // D103 
        BB_PERIPHERAL(GPIOB_IDR,  3),           // D104 	
        BB_PERIPHERAL(GPIOB_IDR,  4)            // D105 	
    };
  

#elif defined (BOARD_maple_RET6) || defined(BOARD_maple)
  // uses http://leaflabs.com/docs/hardware/maple.html#gpio-port-pin-map
  volatile uint32_t* const bb_port_ODR_bit_address[] = {    
    BB_PERIPHERAL(GPIOA_ODR,  3),          //  D0 
    BB_PERIPHERAL(GPIOA_ODR,  2),          //  D1         	      
    BB_PERIPHERAL(GPIOA_ODR,  0),          //  D2 
    BB_PERIPHERAL(GPIOA_ODR,  1),          //  D3 
    BB_PERIPHERAL(GPIOB_ODR,  5),          //  D4 	        	
    BB_PERIPHERAL(GPIOB_ODR,  6),          //  D5 	
    BB_PERIPHERAL(GPIOA_ODR,  8),          //  D6 	
    BB_PERIPHERAL(GPIOA_ODR,  9),          //  D7 	
    BB_PERIPHERAL(GPIOA_ODR,  10),         //  D8 	
    BB_PERIPHERAL(GPIOB_ODR,  7),          //  D9 	
    BB_PERIPHERAL(GPIOA_ODR,  4),          //  D10
    BB_PERIPHERAL(GPIOA_ODR,  7),          //  D11 	
    BB_PERIPHERAL(GPIOA_ODR,  6),          //  D12 	
    BB_PERIPHERAL(GPIOA_ODR,  5),          //  D13	
    BB_PERIPHERAL(GPIOB_ODR,  8),          //  D14 	
    BB_PERIPHERAL(GPIOC_ODR,  0),          //  D15
    BB_PERIPHERAL(GPIOC_ODR,  1),          //  D16
    BB_PERIPHERAL(GPIOC_ODR,  2),          //  D17
    BB_PERIPHERAL(GPIOC_ODR,  3),          //  D18
    BB_PERIPHERAL(GPIOC_ODR,  4),          //  D19
    BB_PERIPHERAL(GPIOC_ODR,  5),          //  D20
    BB_PERIPHERAL(GPIOC_ODR,  13),         //  D21        
    BB_PERIPHERAL(GPIOC_ODR,  14),         //  D22        
    BB_PERIPHERAL(GPIOC_ODR,  15),         //  D23     
    BB_PERIPHERAL(GPIOB_ODR,  9),          //  D24 
    BB_PERIPHERAL(GPIOD_ODR, 2),           //  D25 	       
    BB_PERIPHERAL(GPIOC_ODR,  10),         //  D26
    BB_PERIPHERAL(GPIOB_ODR,  0),          //  D27       
    BB_PERIPHERAL(GPIOB_ODR,  1),          //  D28        
    BB_PERIPHERAL(GPIOB_ODR,  10),         //  D29 	       
    BB_PERIPHERAL(GPIOB_ODR,  11),         //  D30 	        
    BB_PERIPHERAL(GPIOB_ODR,  12),         //  D31 	
    BB_PERIPHERAL(GPIOB_ODR,  13),         //  D32 	        	
    BB_PERIPHERAL(GPIOB_ODR,  14),         //  D33
    BB_PERIPHERAL(GPIOB_ODR,  15),         //  D34 	        	        
    BB_PERIPHERAL(GPIOC_ODR,  6),          //  D35
    BB_PERIPHERAL(GPIOC_ODR,  7),          //  D36        
    BB_PERIPHERAL(GPIOC_ODR,  8),          //  D37
    BB_PERIPHERAL(GPIOC_ODR,  9),          //  D38
    BB_PERIPHERAL(GPIOA_ODR,  13),         //  D39 	                
    BB_PERIPHERAL(GPIOA_ODR,  14),         //  D40 	
    BB_PERIPHERAL(GPIOA_ODR,  15),         //  D41 	
    BB_PERIPHERAL(GPIOB_ODR,  3),          //  D42	
    BB_PERIPHERAL(GPIOB_ODR,  4)           //  D43

  };
  volatile uint32_t* const bb_port_IDR_bit_address[] = {    
    BB_PERIPHERAL(GPIOA_IDR,  3),          //  D0 
    BB_PERIPHERAL(GPIOA_IDR,  2),          //  D1         	      
    BB_PERIPHERAL(GPIOA_IDR,  0),          //  D2 
    BB_PERIPHERAL(GPIOA_IDR,  1),          //  D3 
    BB_PERIPHERAL(GPIOB_IDR,  5),          //  D4 	        	
    BB_PERIPHERAL(GPIOB_IDR,  6),          //  D5 	
    BB_PERIPHERAL(GPIOA_IDR,  8),          //  D6 	
    BB_PERIPHERAL(GPIOA_IDR,  9),          //  D7 	
    BB_PERIPHERAL(GPIOA_IDR,  10),         //  D8 	
    BB_PERIPHERAL(GPIOB_IDR,  7),          //  D9 	
    BB_PERIPHERAL(GPIOA_IDR,  4),          //  D10
    BB_PERIPHERAL(GPIOA_IDR,  7),          //  D11 	
    BB_PERIPHERAL(GPIOA_IDR,  6),          //  D12 	
    BB_PERIPHERAL(GPIOA_IDR,  5),          //  D13	
    BB_PERIPHERAL(GPIOB_IDR,  8),          //  D14 	
    BB_PERIPHERAL(GPIOC_IDR,  0),          //  D15
    BB_PERIPHERAL(GPIOC_IDR,  1),          //  D16
    BB_PERIPHERAL(GPIOC_IDR,  2),          //  D17
    BB_PERIPHERAL(GPIOC_IDR,  3),          //  D18
    BB_PERIPHERAL(GPIOC_IDR,  4),          //  D19
    BB_PERIPHERAL(GPIOC_IDR,  5),          //  D20
    BB_PERIPHERAL(GPIOC_IDR,  13),         //  D21        
    BB_PERIPHERAL(GPIOC_IDR,  14),         //  D22        
    BB_PERIPHERAL(GPIOC_IDR,  15),         //  D23     
    BB_PERIPHERAL(GPIOB_IDR,  9),          //  D24 
    BB_PERIPHERAL(GPIOD_IDR,  2),          //  D25 	       
    BB_PERIPHERAL(GPIOC_IDR,  10),         //  D26
    BB_PERIPHERAL(GPIOB_IDR,  0),          //  D27       
    BB_PERIPHERAL(GPIOB_IDR,  1),          //  D28        
    BB_PERIPHERAL(GPIOB_IDR,  10),         //  D29 	       
    BB_PERIPHERAL(GPIOB_IDR,  11),         //  D30 	        
    BB_PERIPHERAL(GPIOB_IDR,  12),         //  D31 	
    BB_PERIPHERAL(GPIOB_IDR,  13),         //  D32 	        	
    BB_PERIPHERAL(GPIOB_IDR,  14),         //  D33
    BB_PERIPHERAL(GPIOB_IDR,  15),         //  D34 	        	        
    BB_PERIPHERAL(GPIOC_IDR,  6),          //  D35
    BB_PERIPHERAL(GPIOC_IDR,  7),          //  D36        
    BB_PERIPHERAL(GPIOC_IDR,  8),          //  D37
    BB_PERIPHERAL(GPIOC_IDR,  9),          //  D38
    BB_PERIPHERAL(GPIOA_IDR,  13),         //  D39 	                
    BB_PERIPHERAL(GPIOA_IDR,  14),         //  D40 	
    BB_PERIPHERAL(GPIOA_IDR,  15),         //  D41 	
    BB_PERIPHERAL(GPIOB_IDR,  3),          //  D42	
    BB_PERIPHERAL(GPIOB_IDR,  4)           //  D43

  };
#else
#error "digitalWriteFaster only works on the Maple, Maple-Mini, Native, and Ret6."
#endif

#define digitalWriteFaster(pin, value) (*bb_port_ODR_bit_address[pin] = value)

#define digitalReadFaster(pin) (*bb_port_IDR_bit_address[pin])


//This is identical to shiftOut except it will use digitalWriteFast -- see digitalWriteFaster.c
void shiftOutFaster(uint8 dataPin, uint8 clockPin, uint8 bitOrder, uint8 value);
#endif

