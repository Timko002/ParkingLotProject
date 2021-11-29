#include "DBObject.h"
// checks if login is valid
string DBObject::checkLogin(string userName, string pass)
{
    DBObject::command = "select * from users where Username= '" + userName + "' and Password='" + pass + "'"; //checking is this user exist
    DBObject::res = DBObject::Cstm->executeQuery(command);
    if (DBObject::res->next()) {
        return "success";
    }
    else
    {
        return "Err: Username/Password doesn't match records.";
    }
}

// return false if user doesn't exist
// return true if user does exist
bool DBObject::checkUserExists(string userName)
{
    DBObject::command = "select * from users where Username= '" + userName + "'"; //checking is this user exist
    DBObject::res = DBObject::Cstm->executeQuery(command);
    if (DBObject::res->next()) {
        return true;
    }
    else
    {
        return false;
    }
}

void DBObject::createUser(string userName, string pass)
{
    if (!checkUserExists(userName))
    {
        string responseStr = "";
        try {
            DBObject::command = "INSERT INTO users (Username, Password) VALUES ('" + userName + "','" + pass + "')"; //checking is this user exist
            int res1 = DBObject::Cstm->executeUpdate(command);
            if (res1) {
                responseStr = "Success";
            }
            else
            {
                responseStr = "Error";

            }
        }
        catch (sql::SQLException& e) {

            //unknown error
        }
    }
}

void DBObject::bookUser(string userName, string lot, string space_no, string startTime, string endTime)
{
    startTime.replace(2, 1, "_");
    endTime.replace(2, 1, "_");
    try {
        DBObject::command = "update " + lot + " set T" + startTime + " = False where Space_No = " + space_no;
        int res1 = DBObject::Cstm->executeUpdate(command);
        if (DBObject::res) {
            startTime.replace(2, 1, ":");
            endTime.replace(2, 1, ":");
            string command2 = "insert into userlog_table (Username,Start_Time,End_Time) values ('" + userName + "','" + startTime + "','" + endTime + "')";
            int res2 = DBObject::Cstm->executeUpdate(command2);
            if (res2) {
                //cout << "Slot is booked";
            }
            else {
                //cout << "updating userlog table is failed";
            }
        }
    }
    catch (sql::SQLException& e) {

        //unknown error
    }
}

bool DBObject::isReserved(string userName)
{
    DBObject::command = "select * from userlog_table where Username= '" + userName + "'"; //checking is this user exist
    DBObject::res = DBObject::Cstm->executeQuery(command);
    if (DBObject::res->next()) {
        return true;
    }
    else
    {
        return false;
    }
}

DBObject* DBObject::instance()
{
    if (!db)
        db = new DBObject;
    return db;
}
