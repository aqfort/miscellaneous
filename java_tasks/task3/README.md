# Пример использования

Использовалась локальная машина, где в /home/aqfort/java/src/ лежат папки тасков с соответствующими файлами

Промежуточные совпадения по типу .../\<match\>/... отбрасываются

## Ввод_1

```Input
java Grep e.j.v. /home/aqfort/java/src/
```

## Вывод_1

```Output
Pattern: <.*e[a-zA-Z0-9.]j[a-zA-Z0-9.]v[a-zA-Z0-9.][a-zA-Z0-9.]*$>
/home/aqfort/java/src/task1/Coupe.java
/home/aqfort/java/src/task1/Vehicle.java
```

## Ввод_2

```Input
java Grep j.v. /home/aqfort/java/src/
```

## Вывод_2

```Output
Pattern: <.*j[a-zA-Z0-9.]v[a-zA-Z0-9.][a-zA-Z0-9.]*$>
/home/aqfort/java/src/task1/Truck.java
/home/aqfort/java/src/task1/Car.java
/home/aqfort/java/src/task1/Coupe.java
/home/aqfort/java/src/task1/SportsCar.java
/home/aqfort/java/src/task1/App.java
/home/aqfort/java/src/task1/BoxTruck.java
/home/aqfort/java/src/task1/Vehicle.java
/home/aqfort/java/src/task3/Grep.java
/home/aqfort/java/src/task2/Find.java
```

## Ввод_3

```Input
java Grep task /home/aqfort/java/src/
```

## Вывод_3

```Output
Pattern: <.*task[a-zA-Z0-9.]*$>
/home/aqfort/java/src/task1
/home/aqfort/java/src/task3
/home/aqfort/java/src/task2
```
