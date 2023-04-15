#include <unordered_map>

#include "schema.hpp"

#include "../../interfaces/interfaces.hpp"

using SchemaKeyValueMap_t = std::unordered_map<uint32_t, int16_t>;
using SchemaTableMap_t = std::unordered_map<uint32_t, SchemaKeyValueMap_t>;

static bool InitSchemaFieldsForClass(SchemaTableMap_t& tableMap,
                                     const char* className, uint32_t classKey) {
    CSchemaSystemTypeScope* pType =
        interfaces::pSchemaSystem->FindTypeScopeForModule(CLIENT_DLL);
    if (!pType) return false;

    SchemaClassInfoData_t* pClassInfo = pType->FindDeclaredClass(className);
    if (!pClassInfo) {
        tableMap.emplace(classKey, SchemaKeyValueMap_t{});

        LOG("InitSchemaFieldsForClass(): Class '%s' was not found!\n",
            className);
        return false;
    }

    short fieldsSize = pClassInfo->GetFieldsSize();
    SchemaClassFieldData_t* pFields = pClassInfo->GetFields();

    auto& keyValueMap = tableMap[classKey];
    keyValueMap.reserve(fieldsSize);

    for (int i = 0; i < fieldsSize; ++i) {
        SchemaClassFieldData_t& field = pFields[i];
        keyValueMap.emplace(hash_32_fnv1a_const(field.pName), field.uOffset);
    }

    LOG("schemaTableMap[%s] has %llu fields.\n", className, keyValueMap.size());
    return true;
}

int16_t schema::GetOffset(const char* className, uint32_t classKey,
                          const char* memberName, uint32_t memberKey) {
    static SchemaTableMap_t schemaTableMap;
    const auto& tableMapIt = schemaTableMap.find(classKey);
    if (tableMapIt == schemaTableMap.cend()) {
        InitSchemaFieldsForClass(schemaTableMap, className, classKey);
        return GetOffset(className, classKey, memberName, memberKey);
    }

    const SchemaKeyValueMap_t& tableMap = tableMapIt->second;
    if (tableMap.find(memberKey) == tableMap.cend()) {
        LOG("schema::GetOffset(): '%s' was not found in '%s'!\n", memberName,
            className);
        return 0;
    }

    return tableMap.at(memberKey);
}
