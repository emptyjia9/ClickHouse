# Внешние словари {#dicts-external-dicts}

Существует возможность подключать собственные словари из различных источников данных. Источником данных для словаря может быть локальный текстовый/исполняемый файл, HTTP(s) ресурс или другая СУБД. Подробнее смотрите в разделе «[Источники внешних словарей](external-dicts-dict-sources.md)».

ClickHouse:
- Полностью или частично хранит словари в оперативной памяти.
- Периодически обновляет их и динамически подгружает отсутствующие значения.
- Позволяет создавать внешние словари с помощью xml-файлов или [DDL-запросов](../../../sql-reference/statements/create.md#create-dictionary-query).

Конфигурация внешних словарей может находится в одном или нескольких xml-файлах. Путь к конфигурации указывается в параметре [dictionaries\_config](../../../sql-reference/dictionaries/external-dictionaries/external-dicts.md).

Словари могут загружаться при старте сервера или при первом использовании, в зависимости от настройки [dictionaries\_lazy\_load](../../../sql-reference/dictionaries/external-dictionaries/external-dicts.md).

Конфигурационный файл словарей имеет вид:

``` xml
<yandex>
    <comment>Необязательный элемент с любым содержимым. Игнорируется сервером ClickHouse.</comment>

    <!--Необязательный элемент, имя файла с подстановками-->
    <include_from>/etc/metrika.xml</include_from>


    <dictionary>
        <!-- Конфигурация словаря -->
    </dictionary>

    ...

    <dictionary>
        <!-- Конфигурация словаря -->
    </dictionary>
</yandex>
```

В одном файле можно [сконфигурировать](external-dicts-dict.md) произвольное количество словарей.

Если вы создаёте внешние словари [DDL-запросами](../../../sql-reference/statements/create.md#create-dictionary-query), то не задавайте конфигурацию словаря в конфигурации сервера.

!!! attention "Внимание"
    Можно преобразовывать значения по небольшому словарю, описав его в запросе `SELECT` (см. функцию [transform](../../../sql-reference/dictionaries/external-dictionaries/external-dicts.md)). Эта функциональность не связана с внешними словарями.

## Смотрите также {#ext-dicts-see-also}

-   [Настройка внешнего словаря](external-dicts-dict.md)
-   [Хранение словарей в памяти](external-dicts-dict-layout.md)
-   [Обновление словарей](external-dicts-dict-lifetime.md)
-   [Источники внешних словарей](external-dicts-dict-sources.md)
-   [Ключ и поля словаря](external-dicts-dict-structure.md)
-   [Функции для работы с внешними словарями](../../../sql-reference/dictionaries/external-dictionaries/external-dicts.md#ext_dict_functions)

[Оригинальная статья](https://clickhouse.tech/docs/ru/query_language/dicts/external_dicts/) <!--hide-->
