<p align="center">
  <img src="img/svg/banner.svg" alt="BrainfuckPC — 16-разрядный релейный компьютер" width="100%">
</p>

<p align="center">
  <a href="https://github.com/radiolok/brainfuckpc/actions/workflows/build.yml"><img src="https://github.com/radiolok/brainfuckpc/actions/workflows/build.yml/badge.svg" alt="build"></a>
  <a href="LICENCE"><img src="https://img.shields.io/badge/license-GPL--3.0-blue" alt="GPL-3.0"></a>
  <a href="https://habr.com/ru/articles/442732/"><img src="https://img.shields.io/badge/Habr-3%20статьи-6a9fb5" alt="Хабр"></a>
  <a href="https://www.youtube.com/playlist?list=PLHI3L7Als_GPlqEA98NgcnIerBVcbE5Fn"><img src="https://img.shields.io/badge/YouTube-34%20видео-red" alt="YouTube"></a>
  <a href="https://hackaday.io/project/18599-brainfuck-relay-computer"><img src="https://img.shields.io/badge/hackaday.io-build%20log-1a1a1a" alt="hackaday.io"></a>
  <img src="https://img.shields.io/badge/готовность-98%25-d4a72c" alt="status">
</p>

<p align="center"><a href="README.md">English</a> · <b>Русский</b></p>

**BrainfuckPC** — 16-разрядный компьютер фон-неймановской архитектуры,
процессор которого собран на **578 советских герконовых реле**. Родной набор
инструкций — Brainfuck, расширенный ровно настолько (`+10` вместо десяти `+`),
чтобы один релейный сумматор делал всю работу. Машина работает на 25 Гц,
печатает *Hello World!* примерно за шесть секунд и, насколько известно автору,
является самым быстрым релейным компьютером — и одним из самых медленно
считающих компьютеров, которые всё-таки досчитывают.

<p align="center">
  <img src="img/habr/bfpc_and_author_2019.jpg" width="70%" alt="BrainfuckPC и его автор, 2019">
</p>

| | |
|---|---|
| **Архитектура** | фон Нейман, общая память 64К × 16 бит, пословная адресация |
| **Процессор** | 578 герконовых реле (РЭС55 / РЭС64 / РЭС43), 157 логических элементов |
| **Набор инструкций** | [Brainfuck++](doc/instruction_set.md): свёртка `+ - < >`, относительные `JZ`/`JNZ`, `CTRLIO` |
| **Сумматор** | 16 бит, параллельный перенос, ≈ 2 мс на сложение |
| **Тактовая частота** | 25 Гц рабочая, 40 Гц максимум — одна инструкция за такт |
| **Периферия** | плата памяти на SRAM с AVR-загрузчиком, светодиодная матрица 32×16, индикаторы ИВ-6 |
| **Мощность / масса** | 70 Вт · 15 кг |

## Как это работает

![Архитектура](img/svg/architecture.svg)

Brainfuck нужны только лента, указатель на неё и две скобки цикла. Машина
повторяет это буквально: **указатель инструкций** `IP`, **указатель данных**
`AP` и единственный **16-разрядный сумматор**, на один вход которого подаётся
временный регистр, а на другой — 12-битная константа из инструкции.

Любая инструкция — это «прочитать значение, прибавить константу, записать
обратно»: `IP++` при выборке, затем `*AP += n`, `AP += n` или `IP += n` для
перехода. Сумматору с параллельным переносом нужно всего три задержки реле
вместо 32 у сумматора с последовательным переносом — отсюда и скорость.

Такт состоит из двух фаз: по **спаду** тактового сигнала загружается
следующая инструкция, по **фронту** — исполняется. Подробные временные
диаграммы — в [`waveforms/`](waveforms).

![Такт](img/svg/clock-cycle.svg)

![Формат инструкции](img/svg/instruction-format.svg)

Подробнее (на английском): [архитектура](doc/architecture.md) ·
[набор инструкций](doc/instruction_set.md)

## Железо

![Компоновка](img/svg/front-panel.svg)

Каждая логическая функция — это маленький сменный **модуль** на 3–4 реле.
32 модуля образуют **блок**, соединения в котором выполнены монтажом накруткой.
Пять блоков, восемь 16-разрядных защёлок, плата памяти и четыре индикаторных
модуля — вот и вся машина.

| | | |
|:---:|:---:|:---:|
| <img src="img/habr/modules_types.jpg" alt="Модули"> | <img src="img/habr/adder_block_modules.jpg" alt="Блок сумматора"> | <img src="img/habr/wire_wrap_adder_1.jpg" alt="Накрутка"> |
| модули D-триггера, диодный, 2AND/2XOR | блок 16-разрядного сумматора — 32 модуля | ~600 выводов на блок, монтаж накруткой |
| <img src="img/habr/latch_module.jpg" alt="Защёлка"> | <img src="img/habr/iv6_indicator_module.jpg" alt="Модуль ИВ-6"> | <img src="img/habr/memory_board.jpg" alt="Плата памяти"> |
| 16-разрядная защёлка на восьми РЭС43 | индикатор регистров на ИВ-6 | плата памяти со светодиодной матрицей |
| <img src="img/habr/res55_1700hz_scope.jpg" alt="РЭС55 на 1,7 кГц"> | <img src="img/habr/adder_and_regs_running.jpg" alt="Блоки в работе"> | <img src="img/habr/blocks_2018.jpg" alt="Блоки, 2018"> |
| РЭС55 переключается на 1,7 кГц | сумматор и регистры — первый запуск | блоки и индикаторы, 2018 |

Подробнее: [описание железа](doc/hardware.md) — модули, платы и где лежит каждая схема.

## Видео

Вся постройка снята на видео — 34 выпуска от первых набросков в 2017 году до
готовой машины, считающей π:
**[▶ плейлист](https://www.youtube.com/playlist?list=PLHI3L7Als_GPlqEA98NgcnIerBVcbE5Fn)** ·
[список с описанием](doc/videos.md)

| | | |
|:---:|:---:|:---:|
| <a href="https://youtu.be/5hhbGBlP3_4"><img src="https://img.youtube.com/vi/5hhbGBlP3_4/mqdefault.jpg" alt="Пожалуй, самый быстрый релейный компьютер в мире"></a> | <a href="https://youtu.be/CjOYOlJl9wg"><img src="https://img.youtube.com/vi/CjOYOlJl9wg/mqdefault.jpg" alt="Тройной Brainfuck — доклад на митапе, 2018"></a> | <a href="https://youtu.be/UwRxRw0NNDI"><img src="https://img.youtube.com/vi/UwRxRw0NNDI/mqdefault.jpg" alt="Пи = 4! и другие ошибки вычислений на реле"></a> |
| Пожалуй, самый быстрый релейный компьютер в мире | Тройной Brainfuck — доклад на митапе, 2018 | Пи = 4! и другие ошибки вычислений на реле |

## Программы и прошивки

```sh
git clone --recursive https://github.com/radiolok/brainfuckpc
cd brainfuckpc

# компилятор и эмулятор Brainfuck
cmake -S fw/bfutils -B fw/bfutils/build && cmake --build fw/bfutils/build -j
fw/bfutils/bin/bfpp -i bf/examples/hello.b -o hello.bin
fw/bfutils/bin/bfrun -f hello.bin            # Hello World!  Istructions_retired:143

# прошивки AVR для платы памяти и индикаторов
sudo apt install cmake gcc-avr avr-libc binutils-avr
./fw/build.sh                                # → fw/bin/*.hex
```

Каждый push собирается в GitHub Actions; готовые `.hex` прикладываются к
сборке как артефакт `brainfuckpc-firmware`.

Подробнее: [программирование](doc/programming.md) · [прошивки](doc/firmware.md)

## Структура репозитория

```
├── doc/            документация, даташиты, справочные материалы, слайды
├── img/
│   ├── svg/        схемы для документации (+ генераторы в src/)
│   └── habr/       фотографии из статей на Хабре
├── sch/            схемы и платы всех модулей в DipTrace
├── lib/            библиотеки DipTrace: советские реле, посадочные места модулей
├── fw/
│   ├── memorybrd/  прошивка платы памяти (ATmega2560)
│   ├── iv6brd/     прошивка индикаторов ИВ-6 (ATmega168)
│   ├── mcuUtil/    общий планировщик / UART / SPI
│   ├── bfutils/    ⤷ компилятор и эмулятор (сабмодуль)
│   └── build.sh    сборка всех прошивок
├── bf/             программы на Brainfuck и C++-модель для их разработки
├── waveforms/      временные диаграммы всех инструкций (WaveDrom)
├── mech/           механика (DXF / STL)
└── roadmap.md      журнал сборки 2017–2019
```

## Статус

Компьютер **готов на 98%** и исполняет любые программы, не требующие ввода.
Недоделки, оставшиеся при переключении на другие проекты:

- [ ] `CTRLIO.CIN` — ввод с консоли, завязан на логику тактирования (процессор должен останавливаться и ждать данных)
- [ ] логика синхронизации тактов — обвязать три модуля
- [ ] плата памяти rev.2 (только ОЗУ; уберёт залипающий 13-й бит, из-за которого демо идут в 8-разрядном режиме)
- [ ] прошивка программатора и внешний загрузчик
- [ ] печатная машинка Robotron S6130 в роли терминала

## История

![Хронология](img/svg/timeline.svg)

Всё началось с книги Я. Войцеховского «Радиоэлектронные игрушки», где была
описана простая вычислительная машина на телефонных реле. В 2008 году из неё
выросла **РЦВМ-1** — 4-разрядное релейное АЛУ. Десять лет собирания реле
спустя, в ноябре 2016-го, появилась архитектура 16-разрядного BrainfuckPC,
а в 2019 году он исполнил первые программы.

<p align="center">
  <img src="img/habr/rcvm1_alu_2008.jpg" width="32%" alt="РЦВМ-1, 2008">
  <img src="img/habr/render_2017.jpg" width="32%" alt="Рендер 2017">
  <img src="img/habr/infographic_2018.jpg" width="32%" alt="Инфографика 2018">
</p>

Полная история с видео — на Хабре:

| Год | Статья |
|---|---|
| 2017 | [Мои маленькие реле: Brainfuck компьютер это магия](https://habr.com/ru/articles/402629/) — проект |
| 2018 | [Мои маленькие реле: Brainfuck компьютер — это реальность](https://habr.com/ru/articles/411145/) — модули, блоки, первые тесты |
| 2019 | [Мои маленькие реле: Тройной Brainfuck, или что такое безумие](https://habr.com/ru/articles/442732/) — готовая машина |

Серия видео: [34 ролика на YouTube](doc/videos.md).
Журнал сборки на английском: [hackaday.io/project/18599](https://hackaday.io/project/18599-brainfuck-relay-computer).

BrainfuckPC стал первым из трёх «невозможных» компьютеров: за ним последовали
струйный (пневматический) компьютер и **DekatronPC** — компьютер на декатронах.

## Лицензия

[GPL-3.0](LICENCE) © Артём Кашканов
