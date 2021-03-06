#pragma once

#include <Core/NamesAndTypes.h>
#include <Interpreters/DatabaseAndTableWithAlias.h>
#include <Interpreters/InterpreterSelectWithUnionQuery.h>
#include <Storages/IStorage_fwd.h>

namespace DB
{

class ASTSelectQuery;
class Context;
class TableJoin;
struct SelectQueryOptions;

/// Joined tables' columns resolver.
/// We want to get each table structure at most once per table occurance. Or even better once per table.
/// TODO: joins tree with costs to change joins order by CBO.
class JoinedTables
{
public:
    JoinedTables(Context && contex, const ASTSelectQuery & select_query);

    void reset(const ASTSelectQuery & select_query)
    {
        *this = JoinedTables(std::move(context), select_query);
    }

    StoragePtr getLeftTableStorage();
    bool resolveTables();

    /// Make fake tables_with_columns[0] in case we have predefined input in InterpreterSelectQuery
    void makeFakeTable(StoragePtr storage, const Block & source_header);
    std::shared_ptr<TableJoin> makeTableJoin(const ASTSelectQuery & select_query);

    const std::vector<TableWithColumnNamesAndTypes> & tablesWithColumns() const { return tables_with_columns; }

    bool isLeftTableSubquery() const;
    bool isLeftTableFunction() const;
    size_t tablesCount() const { return table_expressions.size(); }

    const StorageID & leftTableID() const { return table_id; }

    void rewriteDistributedInAndJoins(ASTPtr & query);

    std::unique_ptr<InterpreterSelectWithUnionQuery> makeLeftTableSubquery(const SelectQueryOptions & select_options);

private:
    Context context;
    std::vector<const ASTTableExpression *> table_expressions;
    std::vector<TableWithColumnNamesAndTypes> tables_with_columns;

    /// Legacy (duplicated left table values)
    ASTPtr left_table_expression;
    std::optional<DatabaseAndTableWithAlias> left_db_and_table;

    /// left_db_and_table or 'system.one'
    StorageID table_id = StorageID::createEmpty();
};

}
