# Makefile для лабораторной работы №3
# Работает в Windows с GCC

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2

# Объектные файлы
OBJ = src/main.o src/queue.o src/sorts.o src/file_io.o

# Целевая программа
TARGET = lab3.exe

# Правило по умолчанию
all: $(TARGET)

# Сборка программы
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	@echo Программа успешно собрана: $(TARGET)

# Автоматическое правило для компиляции .c в .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	del /Q src\*.o 2>nul || true
	del /Q *.exe 2>nul || true
	del /Q input.txt output.txt 2>nul || true
	@echo Проект очищен

# Запуск
run: $(TARGET)
	$(TARGET)

# Тестирование с файлом
test: $(TARGET)
	@echo 5 3 8 1 9 2 7 4 6 > test.txt
	$(TARGET) --file test.txt
	del /Q test.txt 2>nul || true

# Создание тестового файла
testfile:
	@echo 100 45 23 78 34 89 12 56 90 67 > test.txt
	@echo Тестовый файл создан: test.txt

# Сравнение сортировок на разных размерах
benchmark: $(TARGET)
	@echo Создание тестовых данных...
	@echo 10 5 8 3 9 1 7 2 6 4 > small.txt
	@echo 50 > medium.txt
	@for /l %%i in (1,1,50) do @echo %%i >> medium.txt
	@echo 100 > large.txt
	@for /l %%i in (1,1,100) do @echo %%i >> large.txt

	@echo.
	@echo Тест с 10 элементами:
	@$(TARGET) --file small.txt >nul

	@echo.
	@echo Тест с 50 элементами:
	@$(TARGET) --file medium.txt >nul

	@echo.
	@echo Тест с 100 элементами:
	@$(TARGET) --file large.txt >nul

	@del /Q small.txt medium.txt large.txt 2>nul || true

# Помощь
help:
	@echo ========================================
	@echo   Команды для лабораторной работы №3
	@echo ========================================
	@echo   make          - собрать программу
	@echo   make run      - собрать и запустить
	@echo   make clean    - очистить проект
	@echo   make test     - быстрый тест
	@echo   make testfile - создать тестовый файл
	@echo   make benchmark - сравнение сортировок
	@echo   make help     - показать эту справку
	@echo.
	@echo Для запуска с файлом:
	@echo   lab3.exe --file имя_файла.txt
	@echo ========================================

.PHONY: all clean run test testfile benchmark help