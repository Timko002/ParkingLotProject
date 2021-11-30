#include "DBObject.h"
#include "User.h"
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
    string s5[] = { "9_00","9_15","9_30","9_45","10_00","10_15","10_30","10_45","11_00","11_15","11_30","11_45","12_00","12_15","12_30","12_45","13_00","13_15","13_30","13_45","14_00","14_15","14_30","14_45","15_00","15_15","15_30","15_45","16_00","16_15","16_30","16_45","17_00","17_15","17_30","17_45","18_00" };
    int index;
    std::replace(startTime.begin(), startTime.end(), ':', '_');
    std::replace(endTime.begin(), endTime.end(), ':', '_');

    for (int i = 0; i <= 36; i++) {  // loop to get index no of start time from the array
        if (s5[i] == startTime) {
            index = i;
        }
        else {
            continue;
        }
    }


    for (int j = index; j <= 36; j++) {
        if (s5[j] == endTime) {
            DBObject::command = "update " + lot + " set T" + s5[j] + " = False where Space_No = " + space_no;
            int a = Cstm->executeUpdate(DBObject::command);
            break;
        }
        else {
            DBObject::command = "update " + lot + " set T" + s5[j] + " = False where Space_No = " + space_no;
            int a = Cstm->executeUpdate(DBObject::command);
        }
    }


    try {
        std::replace(startTime.begin(), startTime.end(), '_', ':');
        std::replace(endTime.begin(), endTime.end(), '_', ':');
        string command2 = "insert into userlog_table (Username,Lot_Name,Space_No,Start_Time,End_Time) values ('" + userName + "','" + lot + "','" + space_no + "','" + startTime + "','" + endTime + "')";
        int res2 = DBObject::Cstm->executeUpdate(command2);
        if (res2) {
            //cout << "Slot is booked";
        }
        else {
            //cout << "updating userlog table is failed";
        }
    }
    catch (sql::SQLException& e) {

        //unknown error
    }
}

bool DBObject::isReserved(string userName)
{
    DBObject::command = "select * from userlog_table where Username= '" + userName + "'"; //checking is this user exist
    try {
        DBObject::res = DBObject::Cstm->executeQuery(command);
        while (DBObject::res->next()) {
            User::instance()->set_status("Reserved");
            User::instance()->set_startTime(DBObject::res->getString("Start_Time"));
            User::instance()->set_endTime(DBObject::res->getString("End_Time"));
            User::instance()->setReservedLot(DBObject::res->getString("Lot_Name"));
            User::instance()->setReservedSpot(DBObject::res->getString("Space_No"));
            return true;
        }
        return false;
    }
    catch (sql::SQLException& e) {

        //unknown error
    }
    return false;
}

void DBObject::getUserInfo(string userName)
{
    DBObject::command = "select * from userlog_table where Username= '" + userName + "'"; //checking is this user exist
    DBObject::res = DBObject::Cstm->executeQuery(command);
    if (DBObject::res->next()) {

    }
    else
    {
       //couldn't find user;
    }
}

DBObject* DBObject::instance()
{
    if (!db)
        db = new DBObject;
    return db;
}
