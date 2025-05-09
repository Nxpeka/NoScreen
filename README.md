# NoScreen

This function is used in setwindowaffinity, but unlike the original API function, this function does not create detection vectors, for example, when using setwindowaffinity, this function can easily be detected through getwindowdisplayaffinity, this function is exempt from this, in addition, you can put this protection on any window in the process without interfering with the memory of the process itself.

![mellstroy](https://i.ibb.co/ynzNrTJW/No-Screen-Mellstroy-Edition.gif)

## Как билдит:
1. качаим visual studio с компонентами:
    - Разработка классических приложений на С++
    - Комплект разработки драйверов для Windows
    - MFC for v143 build tools with Spectre migrations
    - ATL for v143 build tools with Spectre migrations
    - ATL for v143 build tools
    - MSVC v143 - VS 2022 C++ build tools
    - MSVC v143 - VS 2022 C++ Spectre-migrated libs
    - Пакет SDK
2. качаим wdk такой же версии как и пакет SDK
3. Ну патом сборка в release режими
4. Собрать решение ну там сам паймеш

## инструкция по использованю: 
0. Отключит антивирус и защито от подделко
1. скачат [lenovo_mapper](https://github.com/estimated1337/lenovo_mapper) или [kdmapper](https://github.com/TheCruZ/kdmapper)
2. сделот билд
3. открыт консол
4. ввести kdmapper.exe kernel.sys
5. открыт user.exe
6. тапат по экранчику

*Вроде lenovo_mapper более крути но эт сам думай пробуй