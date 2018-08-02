#ifndef  _SQLLITE_DB
#define  _SQLLITE_DB
#endif

#pragma once

#include <Windows.h>
#include <string>

#include"sqlite3.h"
using namespace std;


typedef struct Sync
{
	CRITICAL_SECTION _cs;
	Sync() { ::InitializeCriticalSection(&_cs); }
	void LockDB() { ::EnterCriticalSection(&_cs); }
	void UnLockDB() { ::LeaveCriticalSection(&_cs); }
	~Sync() { ::DeleteCriticalSection(&_cs); }
}SyncDB;




class IResult
{
public:

	virtual int	    GetColumnCount() = 0;

	virtual const char* NextColomnName(int iClmnCount) = 0;


	virtual bool  Next() = 0;

	virtual const char*  ColomnData(int clmNum) = 0;

	virtual void Release() = 0;
};



class SQLiteDB : public IResult
{

public:
	SQLiteDB();
	~SQLiteDB();

	bool OpenConnection(string DatabaseName, string DatabaseDir);


	void CloseConnection();


	void BeginTransaction();
	void CommitTransection();


	IResult*  ExcuteSelect(const char *Query);


	UINT	    Excute(const char *Query);

	string GetLastError();

	bool  isConnected();

protected:
	typedef struct SQLLITEConnection
	{
		string		 SQLiteDatabaseName;   //Database Name
		string		 SQLiteDBPath;		   //Databse File Dir
		sqlite3		 *pCon;				   //SQLite Connection Object
		sqlite3_stmt *pRes;				   //SQLite statement object 
	}SQLITECONNECTIONOBJECT;

	SQLITECONNECTIONOBJECT	 *pSQLiteConn;

	SyncDB					 *Sync;

	bool	m_bConnected;      /*Is Connected To DB*/
	bool    m_bConsole;	       /*If Console Application*/
	string  m_strLastError;    /*Last Error String*/
	int	    m_iColumnCount;    /*No.Of Column in Result*/


private:

	int	    GetColumnCount();

	const char* NextColomnName(int iClmnCount);

	bool  Next();

	const char*  ColomnData(int clmNum);

	void Release();

};
