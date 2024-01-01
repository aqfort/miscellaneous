# Пример использования

Промежуточные совпадения по типу .../\<match\>/... отбрасываются

## Ввод

```Input
java Find tar..t /home/aqfort/java/src/
```

## Вывод

```Output
Glob pattern: <*tar??t*>
/home/aqfort/java/src/task2/targetDir
/home/aqfort/java/src/task2/targetDir/target4.txt
/home/aqfort/java/src/task2/someDir/target3.txt
/home/aqfort/java/src/task2/target1.txt
/home/aqfort/java/src/task2/target2.txt
Matched: 5
```

Использовалась локальная машина, где в /home/aqfort/java/src/task2/ лежат соответствующие папки и файлы
