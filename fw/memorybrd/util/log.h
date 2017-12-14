/*Copyright (c) 2014, RLN-tech LLC
All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LOG_H_
#define LOG_H_

#include "uart.h"

//enable this definition to turn on logger notes to port
#define LOGTRACE

#if defined(LOGTRACE)

//enable this definition to turn on debug notes to port
//#define DEBUG

#define log_trace_val(msg, val) uart_puts(msg);uart_print((int16_t)val,10);uart_putc('\n');
#define log_trace_txt(msg, val) uart_puts(msg);uart_puts(val);uart_putc('\n');
#define log_trace(msg) uart_puts(msg);uart_putc('\n');
#else

#define log_trace_val(msg, val) 
#define log_trace_txt(msg, val) 
#define log_trace(msg)

#endif

#if defined(DEBUG)

#define dbg_trace_val(msg, val) uart_puts(msg);uart_print((int16_t)val,10);uart_putc('\n');
#define dbg_trace_txt(msg, val) uart_puts(msg);uart_puts(val);uart_putc('\n');
#define dbg_trace(msg) uart_puts(msg);uart_putc('\n');
#else

#define dbg_trace_val(msg, val)
#define dbg_trace_txt(msg, val)
#define dbg_trace(msg)


#endif

#endif /* LOG_H_ */