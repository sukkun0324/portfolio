//Hearder files for the use of SQL
#include<stdio.h>
#include<Windows.h>
#include<sql.h>
#include<sqlext.h>
#pragma warning (disable:4996)

bool DBConnect(); // Connect to the SQL Server
void DBDisconnect(); // Disconnect from the SQL Server

					 // SQL Environment Variables
SQLHENV hEnv = NULL;
SQLHDBC hDbc = NULL;

bool DBConnect()
{
	SQLRETURN Ret;

	// Allocate the Environment Handle (hEnv)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
	{
		return false;
	}

	// Set attributes of the Environment Handle (hEnv)
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}

	// Allocate the Connection Handle (hDbc)
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
	{
		return false;
	}

	// Connect to the SQL Sever with ODBC name, ID, and PW
	Ret = SQLConnect(hDbc, (SQLCHAR *)"DB01_Server", SQL_NTS, (SQLCHAR *)"DB01", SQL_NTS, (SQLCHAR *)"dbdb01", SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
	{
		return false;
	}

	return true;
}

void DBDisconnect()
{
	SQLDisconnect(hDbc);					// Disconnect from the SQL Server
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);	// Free the Connection Handle
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);	// Free the Environment Handle
}

void implementSQL(static SQLCHAR query[200], int printOrNot)
{
	if (DBConnect() == true)
	{
		SQLHSTMT hStmt;
		SQLRETURN retcode;

		SQLCHAR		ColumnName[30][30];
		SQLSMALLINT ColumnNameLen[30];
		SQLSMALLINT ColumnDataType[30];
		SQLULEN		ColumnDataSize[30];
		SQLSMALLINT ColumnDataDigits[30];
		SQLSMALLINT ColumnDataNullable[30];
		SQLSMALLINT colCount = -1;
		SQLCHAR data[50][40];
		SQLINTEGER nulldata[50];
		int i, j;


		if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) == SQL_SUCCESS)
		{
			retcode = SQLExecDirect(hStmt, query, SQL_NTS);
			if (retcode == SQL_ERROR || retcode == SQL_NO_DATA)
			{
				printf("\t\t* Query Execute Error\n\n");
				return;
			}

			SQLNumResultCols(hStmt, &colCount);

			for (i = 0; i < colCount; i++)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), &nulldata[i]);
			}
			if (printOrNot == 0) // SELECT문 - 결과값을 화면에 출력하기를 원함.
			{
				printf("\n#####################################################################################\n");
				printf("  This Table has these attribute(s)\n");
				for (j = 0; j < colCount; j++)
				{
					SQLDescribeCol(
						hStmt,
						j + 1,
						ColumnName[j],
						50,
						&ColumnNameLen[j],
						&ColumnDataType[j],
						&ColumnDataSize[j],
						&ColumnDataDigits[j],
						&ColumnDataNullable[j]);
					printf(" %s\t", ColumnName[j]);
				}
				printf("\n#####################################################################################\n");
				while (SQLFetch(hStmt) != SQL_NO_DATA)
				{
					for (i = 0; i < colCount; i++)
					{
						if (nulldata[i] == SQL_NULL_DATA)
							printf("NULL ");
						else
						{
							if (i == 0)
								printf("\n");

							printf(" %s\t ", data[i]);
						}
					}
				}
				printf("\n");
			}
			else // QUERY문을 그냥 실행 - UPDATE, DELETE, INSERT문
			{
				printf("\t!!!Query is successfully completed!!!\n");
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}
		DBDisconnect();
	}
	return;
}
void showSchema() //SCHEMA 출력 함수 - 선택해서 확인할 수 있다.
{
	static SQLCHAR query[200];
	int showNum;
	while (1)
	{
		printf("    -----------------------------------------------------------------------------------------------------------------------------\n");
		printf("1. EMPLOYEE      - EMPNO, NAME, PHONE, EMAIL, TITLE, DNO, MANAGER\n");
		printf("2. DEPARTMENT    - DEPTNO, DEPTNAME, FLOOR, TELEPHONE\n");
		//printf("3. SPONSOR       - SPONO, AMOUNT, SDATE, PHONE\n");
		printf("3. VOLUNTEER     - VOLNO, NAME, PHONE, EMAIL, SUPPORT\n");
		printf("4. VETERINARIAN  - VETNO, NAME, BELONG, PHONE\n");
		printf("5. ABANDONDED_DOG - DOGNO, SPECIES, FUR_COLOR, SEX, WEIGHT, MANAGED, ENTERDATE, DISCOVERY_CITY, DISCOVERY_GU, DISCOVERY_DONG\n");
		printf("6. COMMUNITY     - ID, NICKNAME, EMAIL, PHONE, ADDRESS_CITY, ADDRESS_GU, ADDRESS_DONG\n");
		printf("7. FINDED_DOG    - DOGNO, SPECIES, FUR_COLOR, SEX, POSTED, FINDED_DATE, DISCOVERY_CITY, DISCOVERY_GU, DISCOVERY_DONG\n");
		printf("8. LOST_DOG      - DOGNO, SPECIES, FUR_COLOR, SEX, POSTED, LOST_DATE, LOST_CITY, LOST_GU, LOST_DONG\n");
		printf("9. CARE         - DOGNO, VETNO, EMPNO, CHECK, VACCINE\n");
		printf("    -----------------------------------------------------------------------------------------------------------------------------\n");
	returnPoint:
		printf("\t\t어떤 TABLE을 출력합니까? (0을 입력하시면 메인메뉴로 돌아갑니다) ");
		printf("\t>>");
		scanf("%d", &showNum);
		getchar();
		switch (showNum)
		{
		case 0: return;
		case 1: sprintf((char*)query, "SELECT * FROM EMPLOYEE"); break;
		case 2: sprintf((char*)query, "SELECT * FROM DEPARTMENT"); break;
		//case 3: sprintf((char*)query, "SELECT * FROM SPONSOR"); break;
		case 3: sprintf((char*)query, "SELECT * FROM VOLUNTEER"); break;
		case 4: sprintf((char*)query, "SELECT * FROM VETERINARIAN"); break;
		case 5: sprintf((char*)query, "SELECT * FROM ABANDONDED_DOG"); break;
		case 6: sprintf((char*)query, "SELECT * FROM COMMUNITY"); break;
		case 7: sprintf((char*)query, "SELECT * FROM FINDED_DOG"); break;
		case 8: sprintf((char*)query, "SELECT * FROM LOST_DOG"); break;
		case 9: sprintf((char*)query, "SELECT * FROM CARE"); break;
		default: printf("\t\t\t\t<You have to enter another number>\n\n"); getchar(); goto returnPoint;
		}
		implementSQL(query, 0);
	}
	return;
}

void insertQuery(int printNumber) // QUERY문을 직접 받아서 입력.
{
	static SQLCHAR query[200];
	printf("\t\t\t\t\t\t[Query를 입력하세요]\n\t\t ");
	fgets((char*)query, 200, stdin);
	getchar();
	if (printNumber == 0) // 결과 값 출력 - SELECT문에서 작동
		implementSQL(query, 0);
	else // 결과 값 미출력, QUERY문만 실행 - INSERT, UPDATE, DELETE에서 실행.
		implementSQL(query, 1);
	return;
}

void insert()
{
	static SQLCHAR query[200];
	int wayNum, insertNum;
	int empno, vetno, dogid, posted, supp, id, dno, mag, weight, managed;
	char check[10], vaccine[10];
	int spono, amount;
	char nickname[10], email[20], phone[12], addr1[10], addr2[10], addr3[10];
	char species[10], fur[10], sex[6], date[10];
	char name[20], title[10];

Wrong:
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t\t\t\t\t< 어떤 방식으로 QUERY를 수행하시겠습니까? >\n");
	printf("\t\t\t\t\t\t   1. Query 직접 입력. \n");
	printf("\t\t\t\t\t\t   2.  시나리오 실행.\n");
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t>>");
	scanf("%d", &wayNum);
	getchar();
	if (wayNum != 1 && wayNum != 2)
	{
		printf("\t\tWrong!! You choose again!!\n\n");
		goto Wrong;
	}
	while (1)
	{
		if (wayNum == 1)
		{
			insertQuery(1);
			return;
		}
		else
		{
		returnPoint:
			printf("\t시나리오를 선택하세요!\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("1.  COMMUNITY 가입 \n");
			printf("2.  <게시판>임시 보호중인 반려견의 주인을 찾습니다.(COMMUNITY 회원만 가능)\n");
			printf("3.  <게시판>잃어버린 반려견을 찾습니다(COMMUNITY 회원만 가능)\n");
			//printf("4.  유기견 보호센터에 후원하기!\n");
			printf("4.  신입사원 입사!\n");
			printf("5.  봉사자 모집!\n");
			printf("6.  유기견 추가.\n");
			printf("7.  유기견 예방접종.\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
			scanf("%d", &insertNum);
			getchar();
			switch (insertNum)
			{
			case 0:
				return;
			case 1:
				printf("새로운 COMMUNITY ID를 생성합니다 \n");
				printf("ID를 입력하세요(양의 정수, 중복 불가능!) \n>>");
				scanf("%d", &id);
				getchar();
				printf("NICKNAME을 입력하세요(영문숫자 혼합 최대10자리, 중복 불가능!) \n>>");
				scanf("%s", nickname);
				getchar();
				printf("EMAIL을 입력하세요(최대 20자리, 중복 불가능!ex:kim33@gmail.com) \n>>");
				scanf("%s", email);
				getchar();
				printf("PHONE번호를 입력하세요(최대 12자리,중복 불가능!ex:01099998888) \n>>");
				scanf("%s", phone);
				getchar();
				printf("주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("주소(구)(최대 10자리,ex:GWANGJIN) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("주소(동)(최대 10자리,ex:GUNJA) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "INSERT INTO COMMUNITY VALUES(%d,'%s','%s','%s','%s','%s','%s')", id, nickname, email, phone, addr1, addr2, addr3);
				break;
			case 2:
				printf("새로운 '유기견의 주인을 찾는 글'을 생성합니다.\n");
				printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
				scanf("%d", &posted);
				printf("다른 개와 구별되는 번호를 지정해주세요(양의 정수, 중복 불가능) \n>>");
				scanf("%d", &dogid);
				printf("개의 종류를 입력해 주세요.(최대 10자리, ex:MALTESE)\n>> ");
				scanf("%s", species);
				printf("개의 털 색을 입력해 주세요.(최대 10자리)\n>>");
				scanf("%s", fur);
				printf("개의 성별을 입력해 주세요(MALE or FEMALE\n>>");
				scanf("%s", sex);
				printf("발견한 날짜를 입력해 주세요(ex:'2018.05.16')\n>>");
				scanf("%s", date);
				printf("발견한 주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("발견한 주소(구)(최대 10자리,ex:GWANGJIN, NULL가능) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("발견한 주소(동)(최대 10자리,ex:GUNJA, NULL가능) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "INSERT INTO FINDED_DOG VALUES(%d,'%s','%s','%s',%d,'%s','%s','%s','%s')", dogid, species, fur, sex, posted, date, addr1, addr2, addr3);
				break;
			case 3:
				printf("새로운 '잃어버린 개를 찾는 글'을 생성합니다.\n");
				printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
				scanf("%d", &posted);
				printf("다른 개와 구별되는 번호를 지정해주세요(양의 정수, 중복 불가능) \n>>");
				scanf("%d", &dogid);
				printf("개의 종류를 입력해 주세요.(최대 10자리, ex:MALTESE)\n>> ");
				scanf("%s", species);
				printf("개의 털 색을 입력해 주세요.(최대 10자리)\n>>");
				scanf("%s", fur);
				printf("개의 성별을 입력해 주세요(MALE or FEMALE\n>>");
				scanf("%s", sex);
				printf("잃어버린 날짜를 입력해 주세요(ex:'2018.05.16')\n>>");
				scanf("%s", date);
				printf("잃어버린 주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("잃어버린 주소(구)(최대 10자리,ex:GWANGJIN, NULL가능) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("잃어버린 주소(동)(최대 10자리,ex:GUNJA, NULL가능) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "INSERT INTO LOST_DOG VALUES(%d,'%s','%s','%s',%d,'%s','%s','%s','%s')", dogid, species, fur, sex, posted, date, addr1, addr2, addr3);
				break;
			/*case 4:
				printf("후원 해주셔서 감사합니다!\n");
				printf("구별될 수 있는 후원자 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &spono);
				getchar();
				printf("얼마의 금액을 후원 하시겠습니까?\n>>");
				scanf("%d", &amount);
				getchar();
				printf("후원하신 날짜를 입력해 주세요(ex:'2018.05.16')\n>>");
				scanf("%s", date);
				getchar();
				printf("PHONE번호를 입력 하세요(최대 12자리!ex:01099998888)\n>>");
				scanf("%s", phone);
				getchar();
				sprintf((char*)query, "INSERT INTO SPONSOR VALUES(%d,%d,'%s','%s')", spono, amount, date, phone);
				break;*/
			case 4:
				printf("신입사원이 입사 하였습니다!\n");
				printf("구별될 수 있는 사원 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				printf("사원의 부서 번호를 입력해 주세요(기본값 8)\n>>");
				scanf("%d", &dno);
				getchar();
				printf("사원의 상사의 사원 번호를 입력해 주세요\n>>");
				scanf("%d", &mag);
				getchar();
				printf("사원의 이름을 입력해주세요(최대 20자)\n>>");
				scanf("%s", name);
				getchar();
				printf("PHONE번호를 입력 하세요(최대 12자리!ex:01099998888)\n>>");
				scanf("%s", phone);
				getchar();
				printf("EMAIL을 입력하세요(최대 20자리, 중복 불가능!ex:kim33@gmail.com) \n>>");
				scanf("%s", email);
				getchar();
				printf("사원의 직급을 입력해 주세요(최대 10자리) \n>>");
				scanf("%s", title);
				getchar();
				sprintf((char*)query, "INSERT INTO EMPLOYEE VALUES(%d,'%s','%s','%s','%s',%d,%d)", empno, name, phone, email, title, dno, mag);
				break;
			case 5:
				printf("봉사자 지원하기!\n");
				printf("구별될 수 있는 봉사자 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				printf("지원해줄 사원을 입력해 주세요(8번 부서 사원의 사원번호)\n>>");
				scanf("%d", &supp);
				getchar();
				printf("봉사자의 이름을 입력해주세요(최대 20자)\n>>");
				scanf("%s", name);
				getchar();
				printf("PHONE번호를 입력 하세요(최대 12자리!ex:01099998888)\n>>");
				scanf("%s", phone);
				getchar();
				printf("EMAIL을 입력하세요(최대 20자리, 중복 불가능!ex:kim33@gmail.com) \n>>");
				scanf("%s", email);
				getchar();
				sprintf((char*)query, "INSERT INTO VOLUNTEER VALUES(%d,'%s','%s','%s',%d)", empno, name, phone, email, supp);
				break;
			case 6:
				printf("새로운 유기견 데이터를 생성합니다.\n");
				printf("전담 관리 직원의 사원번호를 입력해 주세요(8번 부서 직원)\n>>");
				scanf("%d", &managed);
				getchar();
				printf("다른 개와 구별되는 번호를 지정해주세요(양의 정수, 중복 불가능) \n>>");
				scanf("%d", &dogid);
				getchar();
				printf("개의 종류를 입력해 주세요.(최대 10자리, ex:MALTESE)\n>> ");
				scanf("%s", species);
				getchar();
				printf("개의 털 색을 입력해 주세요.(최대 10자리)\n>>");
				scanf("%s", fur);
				getchar();
				printf("개의 성별을 입력해 주세요(MALE or FEMALE\n>>");
				scanf("%s", sex);
				getchar();
				printf("개의 몸무게를 입력해 주세요(양의정수, 단위 kg)\n>>");
				scanf("%d", &weight);
				getchar();
				printf("입소한 날짜를 입력해 주세요(ex:'2018.05.16')\n>>");
				scanf("%s", date);
				getchar();
				printf("발견한 주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("발견한 주소(구)(최대 10자리,ex:GWANGJIN, NULL가능) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("발견한 주소(동)(최대 10자리,ex:GUNJA, NULL가능) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "INSERT INTO ABANDONDED_DOG VALUES(%d,'%s','%s','%s',%d,%d,'%s','%s','%s','%s')", dogid, species, fur, sex, weight, managed, date, addr1, addr2, addr3);
				break;
			case 7:
				printf("예방 접종& 건강검진!\n");
				printf("관리할 유기견의 번호를 입력해 주세요\n>>");
				scanf("%d", &dogid);
				getchar();
				printf("치료를 맡으신 수의사번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &vetno);
				getchar();
				printf("전담 건강 관리 직원의 사원번호를 입력해 주세요(9번 부서 직원)\n>>");
				scanf("%d", &empno);
				getchar();
				printf("건강검진한 날을 입력해 주세요(ex:'2018.05.16',NULL가능)\n>>");
				scanf("%s", check);
				getchar();
				printf("예방 접종한 날을 입력해 주세요(ex:'2018.05.16',NULL가능)\n>>");
				scanf("%s", vaccine);
				getchar();
				sprintf((char*)query, "INSERT INTO CARE VALUES(%d,%d,%d,'%s','%s')", dogid, vetno, empno, check, vaccine);
				break;
			default:
				getchar();
				printf("\t\tYou choose wrong number\n");
				goto returnPoint;
			}
			implementSQL(query, 1);
			getchar();
		}
	}
}
void deleteTuple()
{
	static SQLCHAR query[200];
	int empno, vetno, dogid, posted, supp, id, dno, mag, weight, managed;
	char check[10], vaccine[10];
	int spono, amount, wayNum, insertNum;
	char nickname[10], email[20], phone[12], addr1[10], addr2[10], addr3[10];
	char species[10], fur[10], sex[6], date[10];
	char name[20], title[10];
	char ID[12];
Wrong:
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t\t\t\t\t< 어떤 방식으로 QUERY를 수행하시겠습니까? >\n");
	printf("\t\t\t\t\t\t   1. Query 직접 입력. \n");
	printf("\t\t\t\t\t\t   2.  시나리오 실행.\n");
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t>>");
	scanf("%d", &wayNum);
	getchar();
	if (wayNum != 1 && wayNum != 2)
	{
		printf("\t\tWrong!! You choose again!!\n\n");
		goto Wrong;
	}
	while (1)
	{
		if (wayNum == 1)
		{
			insertQuery(1);
			return;
		}
		else
		{
		returnPoint:
			printf("\t시나리오를 선택하세요!\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("1.  COMMUNITY 회원탈퇴 \n");
			printf("2.  <게시판>임시 보호중인 반려견의 주인을 찾는 글을 지웁니다.(COMMUNITY 회원만 가능)\n");
			printf("3.  <게시판>잃어버린 반려견을 찾는 글을 지웁니다.(COMMUNITY 회원만 가능)\n");
			printf("4.  직원 데이터 삭제\n");
			printf("5.  봉사자 데이터 삭제\n");
			printf("6.  수의사 데이터 삭제\n");
			printf("7.  유기견 데이터 삭제\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
			scanf("%d", &insertNum);
			getchar();
			switch (insertNum)
			{
			case 0:
				return;
			case 1:
				printf("\t삭제할 COMMUNITY ID를 입력하세요 (ID가 게시한 글들도 함께 삭제 됩니다.) : ");
				scanf("%d", &id);
				getchar();
				sprintf((char*)query, "DELETE FROM COMMUNITY WHERE ID= %d ", id);
				break;
			case 2:
				printf("'유기견의 주인을 찾는 글'을 삭제합니다.\n");
				printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
				scanf("%d", &posted);
				sprintf((char*)query, "SELECT * FROM FINDED_DOG WHERE POSTED= %d ", posted);
				implementSQL(query, 0);
				printf("지우실 글의 개번호를 입력해 주세요\n>>");
				scanf("%d", &dogid);
				getchar();
				sprintf((char*)query, "DELETE FROM FINDED_DOG WHERE DOGNO=%d", dogid);
				break;
			case 3:
				printf("'잃어버린 개를 찾는 글'을 삭제합니다.\n");
				printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
				scanf("%d", &posted);
				sprintf((char*)query, "SELECT * FROM LOST_DOG WHERE POSTED= %d ", posted);
				implementSQL(query, 0);
				printf("지우실 글의 개번호를 입력해 주세요\n>>");
				scanf("%d", &dogid);
				getchar();
				sprintf((char*)query, "DELETE FROM LOST_DOG WHERE DOGNO=%d", dogid);
				break;
			case 4:
				printf("직원 데이터를 삭제합니다.\n");
				printf("구별될 수 있는 사원 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				sprintf((char*)query, "DELETE FROM EMPLOYEE WHERE EMPNO=%d", empno);
				break;
			case 5:
				printf("봉사자 데이터를 삭제합니다\n");
				printf("구별될 수 있는 봉사자 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				sprintf((char*)query, "DELETE FROM VOLUNTEER WHERE VOLNO=%d", empno);
				break;
			case 6:
				printf("수의사 데이터를 삭제합니다\n");
				printf("구별될 수 있는 수의사 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				sprintf((char*)query, "DELETE FROM VETERINARIAN WHERE VETNO=%d", empno);
				break;//1번은 삭제 불가
			case 7:
				printf("유기견 데이터를 삭제합니다. 유기견의 CARE 데이터도 함께 삭제 됩니다.\n");
				printf("구별될 수 있는 유기견 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				sprintf((char*)query, "DELETE FROM VETERINARIAN WHERE VETNO=%d; DELETE FROM CARE WHERE DOG=%d;", empno, empno);
				break;
			default:
				getchar();
				printf("\t\tYou choose wrong number\n");
				goto returnPoint;
			}
			implementSQL(query, 1);
			getchar();
		}
	}
}
void updateTuple()
{
	static SQLCHAR query[200];
	int wayNum, insertNum;
	int empno, vetno, dogid, posted, supp, id, dno, mag, weight, managed;
	char check[10], vaccine[10];
	int spono, amount;
	char nickname[10], email[20], phone[12], addr1[10], addr2[10], addr3[10];
	char species[10], fur[10], sex[6], date[10];
	char name[20], title[10];

Wrong:
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t\t\t\t\t< 어떤 방식으로 QUERY를 수행하시겠습니까? >\n");
	printf("\t\t\t\t\t\t   1. Query 직접 입력. \n");
	printf("\t\t\t\t\t\t   2.  시나리오 실행.\n");
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t>>");
	scanf("%d", &wayNum);
	getchar();
	if (wayNum != 1 && wayNum != 2)
	{
		printf("\t\tWrong!! You choose again!!\n\n");
		goto Wrong;
	}
	while (1)
	{
		if (wayNum == 1)
		{
			insertQuery(1);
			return;
		}
		else
		{
		returnPoint:
			printf("\t시나리오를 선택하세요!\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("1.  COMMUNITY 회원 정보 수정\n");
			printf("2.  <게시판>임시 보호중인 반려견의 주인을 찾는 글을 수정합니다.(COMMUNITY 회원만 가능)\n");
			printf("3.  <게시판>잃어버린 반려견을 찾는 글을 수정합니다.(COMMUNITY 회원만 가능)\n");
			printf("4.  사원 데이터 수정\n");
			printf("5.  봉사자 데이터 수정\n");
			printf("6.  유기견 데이터 수정\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
			scanf("%d", &insertNum);
			getchar();
			switch (insertNum)
			{
			case 0:
				return;
			case 1:
				printf("COMMUNITY ID의 정보를 수정합니다 \n");
				printf("수정할 ID를 입력하세요(양의 정수, 중복 불가능!) \n>>");
				scanf("%d", &id);
				getchar();
				printf("수정할 NICKNAME을 입력하세요(영문숫자 혼합 최대10자리, 중복 불가능!) \n>>");
				scanf("%s", nickname);
				getchar();
				printf("수정할 EMAIL을 입력하세요(최대 20자리, 중복 불가능!ex:kim33@gmail.com) \n>>");
				scanf("%s", email);
				getchar();
				printf("수정할 PHONE번호를 입력하세요(최대 12자리,중복 불가능!ex:01099998888) \n>>");
				scanf("%s", phone);
				getchar();
				printf("수정할 주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("수정할 주소(구)(최대 10자리,ex:GWANGJIN) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("수정할 주소(동)(최대 10자리,ex:GUNJA) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "UPDATE COMMUNITY SET NICKNAME='%s',EMAIL='%s',PHONE='%s',ADDRESS_CITY='%s',ADDRESS_GU='%s',ADDRESS_DONG='%s' WHERE ID=%d", nickname, email, phone, addr1, addr2, addr3, id);
				break;
			case 2:
				printf("'유기견의 주인을 찾는 글'을 수정합니다.\n");
				printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
				scanf("%d", &posted);
				printf("수정할 개의 번호를 입력해주세요.\n>>");
				scanf("%d", &dogid);
				printf("수정할 개의 종류를 입력해 주세요.(최대 10자리, ex:MALTESE)\n>> ");
				scanf("%s", species);
				printf("수정할 개의 털 색을 입력해 주세요.(최대 10자리)\n>>");
				scanf("%s", fur);
				printf("수정할 개의 성별을 입력해 주세요(MALE or FEMALE\n>>");
				scanf("%s", sex);
				printf("수정할 발견한 날짜를 입력해 주세요(ex:'2018.05.16')\n>>");
				scanf("%s", date);
				printf("수정할 발견한 주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("수정할 발견한 주소(구)(최대 10자리,ex:GWANGJIN, NULL가능) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("수정할 발견한 주소(동)(최대 10자리,ex:GUNJA, NULL가능) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "UPDATE FINDED_DOG SET SPECIES='%s',FUR_COLOR='%s',SEX='%s',FINDED_DATE='%s',DISCOVERY_CITY='%s',DISCOVERY_GU='%s',DISCOVERY_DONG='%s'WHERE DOGNO=%d AND POSTED=%d)", species, fur, sex, date, addr1, addr2, addr3, dogid, posted);
				break;
			case 3:
				printf("'잃어버린 개를 찾는 글'을 수정합니다.\n");
				printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
				scanf("%d", &posted);
				printf("수정할 개의 번호를 입력해주세요.\n>>");
				scanf("%d", &dogid);
				printf("수정할 개의 종류를 입력해 주세요.(최대 10자리, ex:MALTESE)\n>> ");
				scanf("%s", species);
				printf("수정할 개의 털 색을 입력해 주세요.(최대 10자리)\n>>");
				scanf("%s", fur);
				printf("수정할 개의 성별을 입력해 주세요(MALE or FEMALE\n>>");
				scanf("%s", sex);
				printf("수정할 발견한 날짜를 입력해 주세요(ex:'2018.05.16')\n>>");
				scanf("%s", date);
				printf("수정할 발견한 주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("수정할 발견한 주소(구)(최대 10자리,ex:GWANGJIN, NULL가능) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("수정할 발견한 주소(동)(최대 10자리,ex:GUNJA, NULL가능) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "UPDATE LOST_DOG SET SPECIES='%s',FUR_COLOR='%s',SEX='%s',LOST_DATE='%s',LOST_CITY='%s',LOST_GU='%s',LOST_DONG='%s'WHERE DOGNO=%d AND POSTED=%d)", species, fur, sex, date, addr1, addr2, addr3, dogid, posted);
				break;
			case 4:
				printf("사원의 데이터를 수정합니다.\n");
				printf("수정할  사원 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				printf("수정할 사원의 부서 번호를 입력해 주세요(기본값 8)\n>>");
				scanf("%d", &dno);
				getchar();
				printf("수정할 사원의 상사의 사원 번호를 입력해 주세요\n>>");
				scanf("%d", &mag);
				getchar();
				printf("수정할 사원의 이름을 입력해주세요(최대 20자)\n>>");
				scanf("%s", name);
				getchar();
				printf("수정할 PHONE번호를 입력 하세요(최대 12자리!ex:01099998888)\n>>");
				scanf("%s", phone);
				getchar();
				printf("수정할 EMAIL을 입력하세요(최대 20자리, 중복 불가능!ex:kim33@gmail.com) \n>>");
				scanf("%s", email);
				getchar();
				printf("수정할 사원의 직급을 입력해 주세요(최대 10자리) \n>>");
				scanf("%s", title);
				getchar();
				sprintf((char*)query, "UPDATE EMPLOYEE SET NAME='%s',PHONE='%s',EMAIL='%s',TITLE='%s',DNO=%d,MANAGER=%d WHERE EMPNO= %d", name, phone, email, title, dno, mag, empno);
				break;
			case 5:
				printf("봉사자 데이터를 수정합니다.\n");
				printf("수정할 봉사자 번호를 입력해 주세요(양의 정수)\n>>");
				scanf("%d", &empno);
				getchar();
				printf("수정할 지원해줄 사원을 입력해 주세요(8번 부서 사원의 사원번호)\n>>");
				scanf("%d", &supp);
				getchar();
				printf("수정할 봉사자의 이름을 입력해주세요(최대 20자)\n>>");
				scanf("%s", name);
				getchar();
				printf("수정할 PHONE번호를 입력 하세요(최대 12자리!ex:01099998888)\n>>");
				scanf("%s", phone);
				getchar();
				printf("수정할 EMAIL을 입력하세요(최대 20자리, 중복 불가능!ex:kim33@gmail.com) \n>>");
				scanf("%s", email);
				getchar();
				sprintf((char*)query, "UPDATE VOLUNTEER SET NAME='%s',PHONE='%s',EMAIL='%s',SUPPORT=%d WHERE VOLNO=%d", name, phone, email, supp, empno);
				break;
			case 6:
				printf("유기견 데이터를 수정합니다.\n");
				printf("수정할 개의 번호를 입력해 주세요(양의 정수, 중복 불가능) \n>>");
				scanf("%d", &dogid);
				getchar();
				printf("수정할 전담 관리 직원의 사원번호를 입력해 주세요(8번 부서 직원)\n>>");
				scanf("%d", &managed);
				getchar();
				printf("수정할 개의 종류를 입력해 주세요.(최대 10자리, ex:MALTESE)\n>> ");
				scanf("%s", species);
				getchar();
				printf("수정할 개의 털 색을 입력해 주세요.(최대 10자리)\n>>");
				scanf("%s", fur);
				getchar();
				printf("수정할 개의 성별을 입력해 주세요(MALE or FEMALE\n>>");
				scanf("%s", sex);
				getchar();
				printf("수정할 개의 몸무게를 입력해 주세요(양의정수, 단위 kg)\n>>");
				scanf("%d", &weight);
				getchar();
				printf("수정할 입소한 날짜를 입력해 주세요(ex:'2018.05.16')\n>>");
				scanf("%s", date);
				getchar();
				printf("수정할 발견한 주소(시)(최대 10자리,ex:SEOUL) \n>>");
				scanf("%s", addr1);
				getchar();
				printf("수정할 발견한 주소(구)(최대 10자리,ex:GWANGJIN, NULL가능) \n>>");
				scanf("%s", addr2);
				getchar();
				printf("수정할 발견한 주소(동)(최대 10자리,ex:GUNJA, NULL가능) \n>>");
				scanf("%s", addr3);
				getchar();
				sprintf((char*)query, "UPDATE ABANDONDED_DOG SET SPECIES='%s',FUR_COLOR='%s',SEX='%s',WEIGHT=%d,MANAGED=%d,ENTERDATE='%s',DISCOVERY_CITY='%s',DISCOVERY_GU='%s',DISCOVERY_DONG='%s' WHERE DOGNO=%d)", species, fur, sex, weight, managed, date, addr1, addr2, addr3, dogid);
				break;
			default:
				getchar();
				printf("\t\tYou choose wrong number\n");
				goto returnPoint;
			}
			implementSQL(query, 1);
			getchar();
		}
	}
}
void selectTuple()
{
	static SQLCHAR query[200];
	int empno, vetno, dogid, posted, supp, id, dno, mag, weight, managed;
	char check[10], vaccine[10];
	int spono, amount, wayNum, insertNum, caseNum;
	char nickname[10], email[20], phone[12], addr1[10], addr2[10], addr3[10];
	char species[10], fur[10], sex[6], date[10];
	char name[20], title[10];
	char ID[12];
Wrong:
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t\t\t\t\t< 어떤 방식으로 QUERY를 수행하시겠습니까? >\n");
	printf("\t\t\t\t\t\t   1. Query 직접 입력. \n");
	printf("\t\t\t\t\t\t   2.  시나리오 실행.\n");
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t>>");
	scanf("%d", &wayNum);
	getchar();
	if (wayNum != 1 && wayNum != 2)
	{
		printf("\t\tWrong!! You choose again!!\n\n");
		goto Wrong;
	}
	while (1)
	{
		if (wayNum == 1)
		{
			insertQuery(0);
			return;
		}
		else
		{
		returnPoint:
			printf("\t시나리오를 선택하세요!\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("1.  COMMUNITY 회원 정보 조회 \n");
			printf("2.  <게시판>임시 보호중인 반려견의 주인을 찾는 글 보기.\n");
			printf("3.  <게시판>잃어버린 반려견을 찾는 글 보기.\n");
			printf("4.  직원 정보 보기\n");
			printf("5.  봉사자 정보 보기\n");
			printf("6.  수의사 정보 보기\n");
			printf("7.  유기견 정보 보기\n");
			printf("8.  유기견들 돌봐주는 체계 보기\n");
			printf("9.  유기견의 건강 상태 보기\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
			scanf("%d", &insertNum);
			getchar();
			switch (insertNum)
			{
			case 0:
				return;
			case 1:
				printf("COMMUNITY 회원 정보 조회합니다.\n");
				printf("1.  모든 회원 정보 보기\n");
				printf("2.  ID로 검색\n");
				printf("3.  닉네임으로 찾기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT * FROM COMMUNITY");
					break;
				case 2:
					printf("\tCOMMUNITY ID를 입력하세요: ");
					scanf("%d", &id);
					getchar();
					sprintf((char*)query, "SELECT * FROM COMMUNITY WHERE ID= %d ", id);
					break;
				case 3:
					printf("\tCOMMUNITY Nickname를 입력하세요: ");
					scanf("%s", nickname);
					getchar();
					sprintf((char*)query, "SELECT * FROM COMMUNITY WHERE NICKNAME= '%s' ", nickname);
					break;
				}
				break;
			case 2:
				printf("'유기견의 주인을 찾는 글'을 조회합니다.\n");
				printf("1.  모든 글 보기\n");
				printf("2.  게시자 ID로 검색\n");
				printf("3.  종으로 찾기\n");
				printf("4.  성별로 찾기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT * FROM FINDED_DOG AS F,COMMUNITY AS C WHERE F.POSTED=C.ID");
					break;
				case 2:
					printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
					scanf("%d", &posted);
					sprintf((char*)query, "SELECT * FROM FINDED_DOG AS F,COMMUNITY AS C WHERE F.POSTED= %d AND F.POSTED=C.ID", posted);
					break;
				case 3:
					printf("찾으실 개의 종류를 검색해 주세요\n>>");
					scanf("%s", species);
					sprintf((char*)query, "SELECT * FROM FINDED_DOG AS F,COMMUNITY AS C WHERE F.POSTED=C.ID AND F.SPECIES= '%s'", species);
					break;
				case 4:
					printf("찾으실 개의 성별 검색해 주세요\n>>");
					scanf("%s", sex);
					sprintf((char*)query, "SELECT * FROM FINDED_DOG AS F,COMMUNITY AS C WHERE F.POSTED=C.ID AND F.SEX= '%s'", sex);
					break;
				}
				break;
			case 3:
				printf("'잃어버린 개를 찾는 글'을 조회합니다.\n");
				printf("1.  모든 글 보기\n");
				printf("2.  게시자 ID로 검색\n");
				printf("3.  종으로 찾기\n");
				printf("4.  성별로 찾기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT * FROM LOST_DOG AS F,COMMUNITY AS C WHERE F.POSTED=C.ID");
					break;
				case 2:
					printf("글 게시자의 COMMUNITY ID를 입력해 주세요\n>>");
					scanf("%d", &posted);
					sprintf((char*)query, "SELECT * FROM LOST_DOG AS F,COMMUNITY AS C WHERE F.POSTED= %d AND F.POSTED=C.ID", posted);
					break;
				case 3:
					printf("찾으실 개의 종류를 검색해 주세요\n>>");
					scanf("%s", species);
					sprintf((char*)query, "SELECT * FROM LOST_DOG AS F,COMMUNITY AS C WHERE F.POSTED=C.ID AND F.SPECIES= '%s'", species);
					break;
				case 4:
					printf("찾으실 개의 성별 검색해 주세요\n>>");
					scanf("%s", sex);
					sprintf((char*)query, "SELECT * FROM LOST_DOG AS F,COMMUNITY AS C WHERE F.POSTED=C.ID AND F.SEX= '%s'", sex);
					break;
				}
				break;
			case 4:
				printf("직원 데이터를 조회합니다.\n");
				printf("1.  모든 직원 보기\n");
				printf("2.  사원 번호로 보기\n");
				printf("3.  부서별 직원 보기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT * FROM EMPLOYEE");
					break;
				case 2:
					printf("직원의 사원번호를 입력해 주세요.\n>>");
					scanf("%d", &empno);
					sprintf((char*)query, "SELECT * FROM EMPLOYEE WHERE EMPNO= %d", empno);
					break;
				case 3:
					printf("부서 번호를 입력해 주세요.\n>>");
					scanf("%d", &dno);
					sprintf((char*)query, "SELECT * FROM EMPLOYEE WHERE DNO= %d", dno);
					break;
				}
				break;
			case 5:
				printf("봉사자 데이터를 조회합니다.\n");
				printf("1.  모든 봉사자 보기\n");
				printf("2.  봉사자 번호로 보기\n");
				printf("3.  봉사자 담당 직원번호로 찾기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT * FROM VOLUNTEER");
					break;
				case 2:
					printf("봉사자 번호를 입력해 주세요.\n>>");
					scanf("%d", &empno);
					sprintf((char*)query, "SELECT * FROM VOLUNTEER WHERE VOLNO= %d", empno);
					break;
				case 3:
					printf("담당 직원 직원번호를 입력해 주세요.\n>>");
					scanf("%d", &dno);
					sprintf((char*)query, "SELECT * FROM VOLUNTEER WHERE SUPPORT= %d", dno);
					break;
				}
				break;
			case 6:
				printf("수의사 데이터를 조회합니다.\n");
				printf("1.  모든 직원 보기\n");
				printf("2.  수의사 번호로 보기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT * FROM VETERINARIAN");
					break;
				case 2:
					printf("수의사 번호를 입력해 주세요.\n>>");
					scanf("%d", &empno);
					sprintf((char*)query, "SELECT * FROM VETERINARIAN WHERE VETNO= %d", empno);
					break;
				}
				break;
			case 7:
				printf("유기견 데이터를 조회합니다.\n");
				printf("1.  모든 유기견 보기\n");
				printf("2.  유기견 번호로 보기\n");
				printf("3.  유기견 담당 직원으로 보기\n");
				printf("4.  종으로 찾기\n");
				printf("5.  성별로 찾기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT * FROM ABANDONDED_DOG");
					break;
				case 2:
					printf("유기견 번호를 입력해 주세요.\n>>");
					scanf("%d", &empno);
					sprintf((char*)query, "SELECT * FROM ABANDONDED_DOG WHERE DOGNO= %d", empno);
					break;
				case 3:
					printf("담당 직원 번호를 입력해 주세요.\n>>");
					scanf("%d", &dno);
					sprintf((char*)query, "SELECT * FROM ABANDONDED_DOG WHERE MANAGED= %d", dno);
					break;
				case 4:
					printf("찾으실 개의 종류를 검색해 주세요\n>>");
					scanf("%s", species);
					sprintf((char*)query, "SELECT * FROM ABANDONDED_DOG WHERE SPECIES= '%s'", species);
					break;
				case 5:
					printf("찾으실 개의 성별 검색해 주세요\n>>");
					scanf("%s", sex);
					sprintf((char*)query, "SELECT * FROM ABANDONDED_DOG WHERE SEX= '%s'", sex);
					break;
				}
				break;
			case 8:
				printf("유기견과 놀아준 데이터 조회합니다.\n");
				printf("1.  모든 유기견 보기\n");
				printf("2.  유기견 번호로 보기\n");
				printf("3.  유기견 담당 직원으로 보기\n");
				printf("4.  봉사자로 찾기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT A.DOGNO,V.VOLNO, V.NAME AS VOLNAME, E.EMPNO, E.NAME AS EMPNAME FROM ABANDONDED_DOG AS A, VOLUNTEER AS V, EMPLOYEE AS E WHERE A.MANAGED=E.EMPNO AND E.EMPNO=V.SUPPORT");
					break;
				case 2:
					printf("유기견 번호를 입력해 주세요.\n>>");
					scanf("%d", &empno);
					sprintf((char*)query, "SELECT A.DOGNO,V.VOLNO, V.NAME AS VOLNAME, E.EMPNO, E.NAME AS EMPNAME FROM ABANDONDED_DOG AS A, VOLUNTEER AS V, EMPLOYEE AS E WHERE A.MANAGED=E.EMPNO AND E.EMPNO=V.SUPPORT AND DOGNO= %d", empno);
					break;
				case 3:
					printf("담당 직원 번호를 입력해 주세요.\n>>");
					scanf("%d", &dno);
					sprintf((char*)query, "SELECT A.DOGNO,V.VOLNO, V.NAME AS VOLNAME, E.EMPNO, E.NAME AS EMPNAME FROM ABANDONDED_DOG AS A, VOLUNTEER AS V, EMPLOYEE AS E WHERE A.MANAGED=E.EMPNO AND E.EMPNO=V.SUPPORT AND EMPNO= %d", dno);
					break;
				case 4:
					printf("봉사자 번호를 입력해 주세요\n>>");
					scanf("%d", &dno);
					sprintf((char*)query, "SELECT A.DOGNO,V.VOLNO, V.NAME AS VOLNAME, E.EMPNO, E.NAME AS EMPNAME FROM ABANDONDED_DOG AS A, VOLUNTEER AS V, EMPLOYEE AS E WHERE A.MANAGED=E.EMPNO AND E.EMPNO=V.SUPPORT AND VOLNO=%d", dno);
					break;
				}
				break;
			case 9:
				printf("유기견의 건강 상태 데이터 조회합니다.\n");
				printf("1.  모든 유기견 보기\n");
				printf("2.  유기견 번호로 보기\n");
				printf("3.  유기견 담당 직원으로 보기\n");
				printf("4.  수의사 번호로 찾기\n");
				printf("    ----------------------------------------------------------------------------------------------------------------    ");
				printf("  번호를 골라 주세요 (0번을 누르면 시작화면으로 돌아갑니다) : ");
				scanf("%d", &caseNum);
				getchar();
				switch (caseNum)
				{
				case 0:
					return;
				case 1:
					sprintf((char*)query, "SELECT A.DOGNO,A.SPECIES,A.WEIGHT, C.CHECKUP, C.VACCINE,V.VETNO, V.NAME AS VETNAME, E.EMPNO, E.NAME AS EMPNAME FROM CARE AS C, ABANDONDED_DOG AS A, VETERINARIAN AS V, EMPLOYEE AS E WHERE C.EMPNO=E.EMPNO AND C.VETNO=V.VETNO AND C.DOG=A.DOGNO");
					break;
				case 2:
					printf("유기견 번호를 입력해 주세요.\n>>");
					scanf("%d", &empno);
					sprintf((char*)query, "SELECT A.DOGNO,A.SPECIES,A.WEIGHT, C.CHECKUP, C.VACCINE,V.VETNO, V.NAME AS VETNAME, E.EMPNO, E.NAME AS EMPNAME FROM CARE AS C, ABANDONDED_DOG AS A, VETERINARIAN AS V, EMPLOYEE AS E WHERE C.EMPNO=E.EMPNO AND C.VETNO=V.VETNO AND C.DOG=A.DOGNO AND C.DOG= %d", empno);
					break;
				case 3:
					printf("담당 직원 번호를 입력해 주세요.\n>>");
					scanf("%d", &dno);
					sprintf((char*)query, "SELECT A.DOGNO,A.SPECIES,A.WEIGHT, C.CHECKUP, C.VACCINE,V.VETNO, V.NAME AS VETNAME, E.EMPNO, E.NAME AS EMPNAME FROM CARE AS C, ABANDONDED_DOG AS A, VETERINARIAN AS V, EMPLOYEE AS E WHERE C.EMPNO=E.EMPNO AND C.VETNO=V.VETNO AND C.DOG=A.DOGNO AND C.EMPNO= %d", dno);
					break;
				case 4:
					printf("수의사 번호를 입력해 주세요\n>>");
					scanf("%d", &dno);
					sprintf((char*)query, "SELECT A.DOGNO,A.SPECIES,A.WEIGHT, C.CHECKUP, C.VACCINE,V.VETNO, V.NAME AS VETNAME, E.EMPNO, E.NAME AS EMPNAME FROM CARE AS C, ABANDONDED_DOG AS A, VETERINARIAN AS V, EMPLOYEE AS E WHERE C.EMPNO=E.EMPNO AND C.VETNO=V.VETNO AND C.DOG=A.DOGNO AND C.VETNO=%d", dno);
					break;
				}
				break;
			default:
				getchar();
				printf("\t\tYou choose wrong number\n");
				goto returnPoint;
			}
			implementSQL(query, 0);
			getchar();
			goto returnPoint;
		}
	}
}
int main() {
	int cmd,usrqeury;
	printf("\n\t\t\t\t\t\tAbandoned dog shelter DBMS\n");
RePoint:
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t\t\t\t\t\t    <SELECT MENU>\t     \n");
	printf("\t\t\t\t\t\t    1.쿼리문 직접 입력받기\t     \n");
	printf("\t\t\t\t\t\t    2.SELECT\t     \n");
	printf("\t\t\t\t\t\t    3.INSERT\t     \n");
	printf("\t\t\t\t\t\t    4.DELETE\t     \n");
	printf("\t\t\t\t\t\t    5.UPDATE\t     \n");
	printf("\t\t\t\t\t\t    6.PRINT\t     \n");
	printf("\t\t\t\t\t\t    7.E X I T    \t     \n");
	printf("    ----------------------------------------------------------------------------------------------------------------    ");
	printf("\t\t\t\t\t\t\t>>");
	scanf("%d", &cmd);
	getchar();
	if (cmd > 0 && cmd < 8)
	{
		switch (cmd)
		{
		case 1: 
			printf("쿼리문의 유형을 선택해 주세요\n1.SELECT문\n2.INSERT,DELETE,UPDATE문\n");
			printf("    ----------------------------------------------------------------------------------------------------------------    ");
			printf("\t\t\t>>");
			scanf("%d",&usrqeury);
			getchar();
			if(usrqeury==1)insertQuery(0);
			else if(usrqeury==2)insertQuery(1);
			else printf("\n\t\t\t\tYOU SELECT WRONG NUMBER.PLEASE TRY AGAIN\n\n\n");
			goto RePoint;
		case 2: selectTuple(); goto RePoint;
		case 3: insert(); goto RePoint;
		case 4: deleteTuple(); goto RePoint;
		case 5: updateTuple(); goto RePoint;
		case 6: showSchema(); goto RePoint;
		case 7: return 0;
		default: break;
		}
	}
	else
	{
		getchar();
		printf("\n\t\t\t\tYOU SELECT WRONG NUMBER.PLEASE TRY AGAIN\n\n\n");
		goto RePoint;
	}
}