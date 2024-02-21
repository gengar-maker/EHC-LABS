# Lab2. Intel advisor

Этап с настройкой окружения для запуска Intel Advisor соответствует аналогичному шагу в предыдущей лабораторной работе.
Запуск Intel Advisor с использованием пользовательского интерфейса (выполняется из консоли с настроенным окружением):
```
C:\Users\k.sandalov>advisor-gui
```

Для создания нового проекта - **Create project**:

<p align="center">
<img src="./data/new/create_project_0.png" alt="image" width="80%" height="auto">
</p>

Выбор имени проекта и его расположение:

<p align="center">
<img src="./data/new/create_project_1.png" alt="image" width="80%" height="auto">
</p>

После этого, для начальной настройки проекта нужно на вкладке **Analysis Target** -> **Survey Hotspots Analysis** выбрать анализируемое приложение, указав полный путь до полученного .exe файла в окне **Application**. Соответственно, аргумены запускаемого приложения (выбран режим **Launch Application**), задаются в окне **Application parameters**.

В рамках лабораторной работы используем тестовое приложение mmult из этого репозитория.
Сперва необходимо собрать его базовую версию со следующими опциями компиляции:
```
add_compile_options(-O3 -Qopt-report=max -debug)
```

<p align="center">
<img src="./data/new/create_project_2.png" alt="image" width="85%" height="auto">
</p>

Дополнительно на вкладке **Analysis Target** -> **Trip Counts and FLOP Analysis** необходимо выбрать пункт **Enable Memory-Level Roofline with cache simulation**:

<p align="center">
<img src="./data/new/create_project_3.png" alt="image" width="85%" height="auto">
</p>

При создании нового проекта первым должно появиться окно с выбором определенного типа анализа или же, **Perspective selector**:

<p align="center">
<img src="./data/new/perspective_selector.png" alt="image" width="85%" height="auto">
</p>

Нужно выбрать **CPU / Memory Roofline Insights**.

В блоке **Analysis Workflow** можно переключиться между разными перспективами а так же подобрать параметры для текущего типа анализа и запустить сбор данных + непосредственно сам анализ.

<p align="center">
<img src="./data/new/analysis_workflow.png" alt="image" width="25%" height="auto">
</p>

По типам анализов:
- **Survey** - начальное определение горячих участков приложение (hotspots).
- **Characterization** - более тяжеловесный анализ, позволяющий определить конкретнее, сколько операций с плавающей точкой было выполнено, сколько раз было вызвано тело анализируемого цикла, дерево вызовов соответствующих функций, замерить трафик уровня L1 и прочее.
Для первого запуска должен быть выбран **Survey** + **Characterization (FLOP)**, сравнить время их выполнения.
> Задание:
> Результаты сравнения добавить в отчет. Время выполнения анализа можно найти на вкладке **Summary** в блоке **Collection Details**:

<p align="center">
<img src="./data/new/collection_details.png" alt="image" width="75%" height="auto">
</p>

**Summary**:  
На этой вкладке приведены общие сведения о производительности приложения:
- Количество выполняемых потоков
- Время работы программы от старта выполнения первого потока до завершения последнего
- Используемый набор векторных инструкций
- Доля векторизованных вычислений
- > GFLOPS = FLOPs / Seconds (аналогично и INTOPS)
- > ArithmeticIntensity(AI) = FLOPs / Bytes (отношение кол-ва вычислений к кол-ву запрошенных для этого байтов из памяти)

<p align="center">
<img src="./data/new/summary_0.png" alt="image" width="75%" height="auto">
</p>

- Теоретические пиковые значения производительности для данной платформы и реально задействованная мощность:

<p align="center">
<img src="./data/new/theoretical_peaks.png" alt="image" width="75%" height="auto">
</p>

Тут же можно найти рекомендации, применимые глобально ко всему приложению, например: Использовать более широкий набор инструкций.

> Задание:
> Зафиксировать время выполнения программы, факт использования векторных инструкций, текущие GFLOPS и AI для приложения. Пиковые значения пропускной способности вычислительной системы.

Топ самых тяжелых хотспотов и рекомендации для них. Подробнее про анализ хотспотов на вкладке **Survey and Roofline**:

<p align="center">
<img src="./data/new/summary_1.png" alt="image" width="75%" height="auto">
</p>

**Roofline**:

<p align="center">
<img src="./data/new/roofline.png" alt="image" width="75%" height="auto">
</p>

На графике руфлайна наглядно отображены ограничения пропускной способности (вычислительной и подсистемы памяти), а также то, насколько эффективно их использует тестовое приложение. На графике отображаются точки, характеризующие производительность самых горячих участков тестового приложения. И в данном случае, это цикл на строке 45 в mmult.cpp. Для этой точки вычисляются значения GFLOPS/GINTOPS и AI, а так же, исходя из используемого набора инструкций, типа операций (FP или INT) и конфигурации подсистемы памяти ограничивающие ее крыши.

Соответственно, ограничением производительности будет служить `MIN(peakMemBandwidth x AI, peakGFLOPS)`

**Survey**:

<p align="center">
<img src="./data/new/survey_hotspots.png" alt="image" width="75%" height="auto">
</p>

Bottom-up представление списка хотспотов приложения в виде таблицы с performance метриками.

> Задание:
> Определить главный хотспот. Затем выделить ограничивающие его крыши, зафиксировать в отчете.

Ниже вкладки:
 
**Source**:

<p align="center">
<img src="./data/new/source.png" alt="image" width="75%" height="auto">
</p>

Выделено непосредственно место в исходном коде, соответствующее выбранному хотспоту.
 
**Top Down**

<p align="center">
<img src="./data/new/top-down.png" alt="image" width="85%" height="auto">
</p>

Дерево вызовов, для выбранного хотспота. Соответственно, для одного хотспота может быть выделено сразу несколько стеков вызовов. И тут уже можно посмотреть долю каждого в суммарном времени для хотспота.
 
**Code Analytics** - суммарная информация по хостпоту + по миксу инструкций для него (соотношение разных типов инструкций - memory vs compute)
 
**Recommendations**

<p align="center">
<img src="./data/new/recommendations.png" alt="image" width="95%" height="auto">
</p>

То, на что стоит обратить большее внимание. Довольно важной частью данного инструмента является система предоставления рекомендаций по анализируемому коду, советы, на что стоит обратить внимание, и даже, возможно, как можно исправить те или иные проблемы с производительностью приложения.

> Далее перед любыми модификациями приложения необходимо делать снэпшоты:
> <p align="center">
> <img src="./data/new/snapshot.png" alt="image" width="75%" height="auto">
> </p>
> <p align="center">
> <img src="./data/new/snapshot_1.png" alt="image" width="75%" height="auto">
> </p>
>
> Снимки профиля, которые далее можно будет сравнивать между собой.

Итак, в данном примере нам предлагается две ракомендации:
- Использовать более широкий набор инструкций + FMA
- Собрать Roofline для всех уровней памяти.

Первое выполнять пока нет смысла, так как в самом коде у нас явно отключена векторизация. Тогда попробуем собрать Memory Level Roofline.

Для этого необходимо в панели **Analysis Workflow**, в **Characterization** блоке выбрать пункт **Cache Simulation** и пересобрать отчет.

<p align="center">
<img src="./data/new/memory_level_roofline.png" alt="image" width="95%" height="auto">
</p>

И теперь по двойному клику на точку на графике руфлайна раскроется раскладка для данного хотспота по утилизации различных уровней подсистемы памяти.

<p align="center">
<img src="./data/new/run_map_recommendation.png" alt="image" width="95%" height="auto">
</p>

А в рекомендациях появится новая опция-предложение: запустить MAP анализ, который позволит определить паттерны доступа к памяти в рамках хотспота.

Для этого, во-первых, необходимо выделить интересующие нас хотспоты:

<p align="center">
<img src="./data/new/select_hotspots.png" alt="image" width="95%" height="auto">
</p>

И выбрать в панели **Analysis Workflow** новый анализ - **Memory Access Patterns** и запустить его.

Третья вкладка **Refinement Reports**:

Тут можно найти отчет по проведенному MAP анализу:

<p align="center">
<img src="./data/new/map_report.png" alt="image" width="75%" height="auto">
</p>

Где, собственно, и написано, что в нашей программе, в хотспоте, обнаружен неэффективный паттерн доступа к памяти. А ниже приведены рокомендации, как от этого можно избавиться:

<p align="center">
<img src="./data/new/reorder_loop_recommendation.png" alt="image" width="75%" height="auto">
</p>

> Сохраняем снэпшот и применяем исправления в коде. Снэпшот приложить к отчету. Можно собрать все в архив и сохранить для дальнейшей отправки преподавателю.

Memory Level Roofline для новой версии приложения:

<p align="center">
<img src="./data/new/memory_level_roofline_new_traffic.png" alt="image" width="75%" height="auto">
</p>

> Доп. вопрос: о чем на рисунке выше говорит подобное расположение точек для разных уровней памяти на графике руффлайна.

Теперь можно сравнить две версии отчета соотв. разным версиям приложения:

<p align="center">
<img src="./data/new/compare_results.png" alt="image" width="45%" height="auto">
</p>

Добавляем сохраненный ранее снэпшот и получаем следующую картинку:

<p align="center">
<img src="./data/new/compared_results.png" alt="image" width="75%" height="auto">
</p>

Наглядно видно прирост производительности.

> Задание: добавить векторизацию `#pragma novector` --> `#pragma vector`. Сравнить результат выполенния векторизованного кода с невекторизованным.
> Использовать AVX  
> `add_compile_options(-O3 -Qopt-report=max -debug /QxCORE-AVX2 /Qalign-loops:32)`