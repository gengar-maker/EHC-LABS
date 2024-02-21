# Lab1. Настройка окружения. Некоторые методы повышения производительности приложения. Эффективность работы с подсистемой памяти. Векторизация.
## Подготовка к выполнению лабораторных работ

1. Необходимо установить инструменты из пакета __Intel oneAPI__:  
    - compiler
    - advisor
    - vtune
    - inspector
    > Первые три доступны в рамках __Intel oneAPI Base Toolkit__. Последний в __Intel oneAPI HPC Toolkit__.

2. Настройка окружения  
    Прежде всего нужно выполнить скрипт `setvars.bat`, который располагается в корневой папке с установленными иснтрументами из пакета __oneAPI__. Например, путь до него может быть следующим:  
    ```
    "C:\Program Files (x86)\Intel\oneAPI\setvars.bat"
    ```
    Для запуска скрипта нужно открыть командную строку: `win + s` -> ищем `cmd` (Командная строка) и запускаем это приложение. Далее в открывшейся командной строке вводим полный путь до скрипта, описанного выше, после чего в консоли появится следующее:
    ```
    Microsoft Windows [Version 10.0.19044.2728]
    (c) Корпорация Майкрософт (Microsoft Corporation). Все права защищены.

    C:\Users\k.sandalov>"C:\Program Files (x86)\Intel\oneAPI\setvars.bat"
    :: initializing oneAPI environment...
    Initializing Visual Studio command-line environment...
    Visual Studio version 17.6.1 environment configured.
    "C:\Program Files\Microsoft Visual Studio\2022\Community\"
    Visual Studio command-line environment initialized for: 'x64'
    :  advisor -- latest
    :  compiler -- latest
    :  debugger -- latest
    :  dev-utilities -- latest
    :  dpl -- latest
    :  tbb -- latest
    :  vtune -- latest
    :: oneAPI environment initialized ::

    C:\Users\k.sandalov>
    ```

    Затем открываем IDE, используя эту же командную строку. И в целом, все инструменты разработки и анализа можно запускать в этой среде.
    В качестве возможных средств разработки предлагается рассмотреть VS Code или же просто Visual Studio (версия от 2016 года или новее).
    - VS Code
        
        Для запуска VS Code можно ввести команду в терминале:
        ```
        C:\Users\k.sandalov>code
        ```
        Для работы с проектом в VS Code нужны следующие расширения (Скачать можно на вкладке *Extensions*):    
        
        <p align="center">
        <img src="./data/vs_code_ext_1.png" alt="image" width="65%" height="auto">
        </p>  
        
        <p align="center">
        <img src="./data/vs_code_ext_2.png" alt="image" width="65%" height="auto">
        </p>
        
        Далее в открывшемся окне переходим в верхнем меню к выбору папки, в которой располагается проект(корневая директория проекта): 
        
        <p align="center">
        <img src="./data/vs_code_1.png" alt="image" width="50%" height="auto">
        </p>

        После открытия папки с проектом должно появиться сообщение с предложением сконфигурировать CMake проект, необходимо сделать это:

        <p align="center">
        <img src="./data/vs_code_3.png" alt="image" width="60%" height="auto">
        </p>

        Для удобной работы с CMake проектом можно воспользоваться меню слева:

        <p align="center">
        <img src="./data/configure_cmake_project.png" alt="image" width="60%" height="auto">
        </p>

        Например, в пункте **Configure** первой строчкой можно выбрать используемые средства для сборки проекта (в нашем случае unspecified)

        <p align="center">
        <img src="./data/building_toolkit.png" alt="image" width="60%" height="auto">
        </p>

    - Visual Studio

        Для запуска Visual Studio используем команду:
        ```
        C:\Users\k.sandalov>devenv
        ```  
        Далее необходимо так же, просто открыть папку с проектом:

        <p align="center">
        <img src="./data/vs_open_folder.png" alt="image" width="60%" height="auto">
        </p>

        В случае, если была корректно выбрана корневая директория проекта и настроено окружение, Visual Studio успешно сможет настроить CMake проект:

        <p align="center">
        <img src="./data/vs_cmake_configure.png" alt="image" width="60%" height="auto">
        </p>

        Далее настройки проекта в первую очередь будут браться из файла `CMakeLists.txt` (смотрите справа в обозревателе решений). Однако так же есть возможность настраивать его через файл `CMakeSettings.json`. Для этого можно использовать переменные и кэш CMake:

        <p align="center">
        <img src="./data/vs_cmake_settings.png" alt="image" width="60%" height="auto">
        </p>

        А для того, чтобы заново переконфигурировать проект можно заново создать кэш CMake, если до этого обновили значения каких-то переменных, чтобы использовались актуальные значения (Удалить кэш и выполнить перенастройку):

        <p align="center">
        <img src="./data/vs_menu_configure.png" alt="image" width="60%" height="auto">
        </p>

        Для сборки используем пункт меню сборка -> перестроить все:

        <p align="center">
        <img src="./data/vs_menu_build.png" alt="image" width="60%" height="auto">
        </p>

 ## Методы повышения эффективности работы с подсистемой памяти. Векторизация.

1. **MMULT**  
    TBD
2. **SOA_TO_AOS**  
    TBD
3. **VECTORIZATION_PEEL_BODY_REMAINDER**  
    TBD
4. **VECTORIZATION_MAP**  
    TBD
5. **VECTORIZED_FUNCTIONS**  
    TBD

