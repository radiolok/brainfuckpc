/*
 * default_definitions.inc
 *
 *  Created: 23.09.2016 14:15:13
 *  Author: Dmitry Pogrebnyak (http://aterlux.ru/)
 */ 


 /* Если данный файл используется в проекте Atmel Studio, то файл с определениями подключен неявно
   (Не забудьте выбрать правильный тип МК в свойствах проекта).
   В противном случае, необходимо подключить файл с определениями, соответствующими МК
   If this file used as part of the Atmel Studio project, then definitions are included implicitely
   (Do not forget to select proper MK type in the projects properties).
   Else proper file with definitions for the MCU should be included */
// .include "m88PAdef.inc" // Atmega88PA
// .include "m328Pdef.inc" // Atmega328P
// .include "m8Adef.inc"   // Atmega8A
// etc.

 /* HARDWARE_ID
  Ровно 14 символов, которые возвращаются в ответе blst и идентифицируют оборудование. 
  Сам код .db находится внизу файла UARTBootloader.asm
  Exactly 14 symbols that returned with blst reply, to identify hardware. Place your own here.
  Actual .db code is placed at the end of the UARTBootloader.asm file
*/
#define HARDWARE_ID "BrainfuckPCiv6"

/* Определите частоту процессора
   define the CPU frequency */
.equ F_CPU = 8000000

/* Определите желаемую скорость UART.
   define the desired UART frequency.
   Действительная скорость порта может отличаться от заданной, её можно вычислить по формулам ниже:
   Actual UART speed may differ from defined one. It could be calculated by the formulas below:
   X = (UART_2X==1) ? F_CPU / 8 : F_CPU / 16
   acutal UART speed = X / round(X / UART_SPEED)

   Примеры/examples:

   F_CPU     UART_SPEED   UART_2X  Actual Speed  разница/difference
   8000000   38400        0/1      38462         +0.2%
   8000000   115200       0        125000        +8.5% (критично/critical)
   8000000   115200       1        111111        -3.5% (могут быть ошибки при передаче/may cause errors)
   12000000  115200       0/1      115384        +0.2%
   16000000  38400        0/1      38462         +0.2%
   16000000  115200       0        111111        -3.5% (могут быть ошибки при передаче/may cause errors)
   16000000  115200       1        117647        +2.1% (высоковато, но не критично/high, but not critical)
   20000000  115200       1        113636        -1.3%
   */
.equ UART_SPEED = 38400

/* Определите UART_2X=1 чтобы использовать опцию двойной скорости для UART
   define UART_2X=1 to enable double speed option */
.equ UART_2X = 0

/* UART_PARITY - бит чётности:
   0 - none/нет
   1 - odd/нечётный
   2 - even/чётный */
.equ UART_PARITY = 0

/* UART_STOP_BITS  Количество стоповых битов 1 или 2
   Number of stop bits 1 or 2 */
.equ UART_STOP_BITS = 1

/* BLINKER - мигающий светодиод, сигнализирующий о работе загрузчика. 
   Укажите BLINKER = 1 - чтобы включить эту опцию, BLINKER = 0 - чтобы выключить.
   BLINKER_PATTERN - шаблон мигания. NORMAL - сразу после запуска загрузчика, READY - после выполнения команды BLST, FLASHING - после начала записи первой страницы.
   Существует счётчик, циклически изменяющий своё значение от 0 до 255. Скорость его изменения пропорциональна частоте ЦП, и приблизительно равна 16 изменениям в секунду при частоте 8МГц.
   Над этим счётчиком и шаблоном выполняется опирация битовое И. Если результат операции равен нулю - светодиод зажигается (высокий уровень на выходе), иначе - гасится (низкий уровень)

   BLINKER - flashing LED, to signal bootloader activity
   Set BLINKER = 1 - to enable this option, BLINKER = 0 - to disable.
   BLINKER_PATTERN - patter of LED blinking. NORMAL - just after bootloader started, READY - after BLST, FLASHING - after first page started to be written.
   There is a counter, which cyclically increments from 0 to 255. It's change speed is proportional to CPU frequency, roughly at level of 16 changes per second, when running at 8MHz
   Bitwise AND is perfomed over this number and the pattern. If operation result is zero - the LED is being enabled (high level at output), otherwise - disabled (low level)

   Примеры шаблонов/examples of patterns:
   0x00 - Постоянно включен / constantly enabled
   0x01 - Быстро мигает / fast blinking 
   0x08 - Медленно мигает (~1раз в секунду при 8МГц) / slow blinking (~1 per second @8MHz)
   0x0A - Серии из двух вспышек / series of two flashes
   0x12 - Серии из четырёх вспышек / series of four flashes
   (чтобы увеличить скорость мигания, разделите числа на 2, чтобы уменьшить - умножьте 
    divide numbers by two to increase blinking speed, multiply to decrease)
*/
.equ BLINKER = 0
.equ BLINKER_PORT = PORTB
.equ BLINKER_DDR = DDRB
.equ BLINKER_PIN_NUM = 4

.equ BLINKER_PATTERN_NORMAL = 0x08
.equ BLINKER_PATTERN_READY = 0x0A
.equ BLINKER_PATTERN_FLASHING = 0x01


/*
  MAGIC - это специальное число которое сохраняется в одной из ячеек EEPROM.
  При запуске, загрузчик читает значение этой ячейки. Если значение отличается от заданного, то происходит запуск загрузчика, 
  а перехода к ПО не происходит. Когда начинается процесс прошивки и загружена первая страница, в указанную ячейку записывается 
  значение 0xFF, таким образом, если процесс загрузки будет прерван, при следующем старте ПО не будет запущенно, а запустится
  загрузчик.
  При выходе (команда BLXT), если процесс загрузки был начат (загружена хотя бы одна страница), и если MAGIC_WRITE_WHEN_FLASHED == 1,
  то в указанную ячейку записывается указанное значение. При следующем запуске будет осуществлён переход сразу к ПО.
  Если MAGIC_WRITE_WHEN_FLASHED == 0, то ПО само должно установить это значение, дабы исключить запуск загрузчика.
  Чтобы отключить эту опцию совсем, закомментируйте строку, определяющую MAGIC

  MAGIC - it is a special number being stored in a one of the EEPROM locations
  When started, bootloader reads value of this EEPROM location, and if the value differs from defined one, then bootloader is being 
  started, and jump to the main firmware will not occur. When the flashing process is started and the first page is loaded, 
  this EEPROM location is filled with 0xFF, therefore, if the flashing process will be interrupted, next time firmware will not be 
  started, and bootloader will be started instead.
  During exit (command BLXT), if the flashing process was started (at least one page was loaded), and if MAGIC_WRITE_WHEN_FLASHED == 1,
  then this location is filled with specified value. Next time, when power-on, the bootloader will not start, but will jump directly
  to the main firmware.
  If MAGIC_WRITE_WHEN_FLASHED == 0, then firmware itself is obligated to write this value to prevent the bootloader to start.
  To disable this option, comment out the line defining MAGIC.
*/
.equ MAGIC = 0xAC
.equ MAGIC_WRITE_WHEN_FLASHED = 1
.equ MAGIC_EEPROM_ADDRESS = EEPROMEND

/*
   Метод принудительного запуска бутлоадера при включении питания
   0 - опция принудительного запуска отключена
   1 - низкий уровень на указанном входе (включается подтягивающий резистор)
   2 - высокий уровень на указанном входе (внешний стягивающйи резистор)
   3 - два указанных вывода замкнуты между собой перемычкой
   4 - низкий уровень на обоих указанных входах (включаются подтягивающие резисторы)

   a method for the forced start of the bootloader
   0 - forced start is disabled
   1 - low level on the selected pin (pull-up is enabled)
   2 - high level on the selected pin (external pull-down)
   3 - two selected pins are coupled by a jumper
   4 - low level on both selected pins (pull-ups are enabled)
*/
.equ FORCE_METHOD = 1
.equ FORCE_PORT = PORTB
.equ FORCE_DDR = DDRB
.equ FORCE_PIN = PINB
.equ FORCE_PIN_NUM = 6
// Ниже для второго пина для методов 3 и 4, Below is for the second pin for methods 3 and 4
.equ FORCE_PORT2 = PORTB
.equ FORCE_DDR2 = DDRB
.equ FORCE_PIN2 = PINB
.equ FORCE_PIN_NUM2 = 5
