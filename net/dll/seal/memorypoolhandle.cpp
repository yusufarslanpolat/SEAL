// SEALDll
#include "stdafx.h"
#include "memorypoolhandle.h"
#include "utilities.h"

// SEAL
#include "seal/memorymanager.h"

using namespace std;
using namespace seal;
using namespace seal::dll;


SEALDLL HRESULT SEALCALL MemoryPoolHandle_Create1(void** handle)
{
    IfNullRet(handle, E_POINTER);

    MemoryPoolHandle* handleptr = new MemoryPoolHandle();
    *handle = handleptr;
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_Create2(void* otherptr, void** handle)
{
    MemoryPoolHandle* other = FromVoid<MemoryPoolHandle>(otherptr);
    IfNullRet(other, E_POINTER);
    IfNullRet(handle, E_POINTER);

    MemoryPoolHandle* handleptr = new MemoryPoolHandle(*other);
    *handle = handleptr;
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_Destroy(void* thisptr)
{
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(thisptr);
    IfNullRet(handle, E_POINTER);

    delete handle;
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_Set(void* thisptr, void* assignptr)
{
    MemoryPoolHandle* handle = FromVoid<MemoryPoolHandle>(thisptr);
    IfNullRet(handle, E_POINTER);
    MemoryPoolHandle* assign = FromVoid<MemoryPoolHandle>(assignptr);
    IfNullRet(assign, E_POINTER);

    *handle = *assign;
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_Global(void** handle)
{
    IfNullRet(handle, E_POINTER);

    MemoryPoolHandle global = MemoryPoolHandle::Global();
    MemoryPoolHandle* handleptr = new MemoryPoolHandle(move(global));
    *handle = handleptr;
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_ThreadLocal(void** handle)
{
    IfNullRet(handle, E_POINTER);

    MemoryPoolHandle threadlocal = MemoryPoolHandle::ThreadLocal();
    MemoryPoolHandle* handleptr = new MemoryPoolHandle(move(threadlocal));
    *handle = handleptr;
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_New(bool clear_on_destruction, void** handle)
{
    IfNullRet(handle, E_POINTER);

    MemoryPoolHandle newhandle = MemoryPoolHandle::New(clear_on_destruction);
    MemoryPoolHandle* handleptr = new MemoryPoolHandle(move(newhandle));
    *handle = handleptr;
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_PoolCount(void* thisptr, uint64_t* count)
{
    MemoryPoolHandle* pool = FromVoid<MemoryPoolHandle>(thisptr);
    IfNullRet(pool, E_POINTER);
    IfNullRet(count, E_POINTER);

    try
    {
        *count = pool->pool_count();
        return S_OK;
    }
    catch (const logic_error&)
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_AllocByteCount(void* thisptr, uint64_t* count)
{
    MemoryPoolHandle* pool = FromVoid<MemoryPoolHandle>(thisptr);
    IfNullRet(pool, E_POINTER);
    IfNullRet(count, E_POINTER);

    try
    {
        *count = pool->alloc_byte_count();
        return S_OK;
    }
    catch (const logic_error&)
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_IsInitialized(void* thisptr, bool* result)
{
    MemoryPoolHandle* pool = FromVoid<MemoryPoolHandle>(thisptr);
    IfNullRet(pool, E_POINTER);
    IfNullRet(result, E_POINTER);

    *result = (bool)(*pool);
    return S_OK;
}

SEALDLL HRESULT SEALCALL MemoryPoolHandle_Equals(void* thisptr, void* otherptr, bool* result)
{
    MemoryPoolHandle* pool = FromVoid<MemoryPoolHandle>(thisptr);
    IfNullRet(pool, E_POINTER);
    MemoryPoolHandle* other = FromVoid<MemoryPoolHandle>(otherptr);
    IfNullRet(other, E_POINTER);
    IfNullRet(result, E_POINTER);

    *result = (*pool == *other);
    return S_OK;
}