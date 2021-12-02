#include "DBObject.h"
#include "User.h"
// checks if login is valid
string DBObject::checkLogin(string userName, string pass)
{
    DBObject::command = "select * from users where Username= '" + userName + "' and Password='" + pass + "'"; //checking is this user exist
    DBObject::res = DBObject::Cstm->executeQuery(command);
    if (DBObject::res->next()) {
        User::instance()->set_user(userName);
        User::instance()->set_status((DBObject::res->getString("Status")));
        if (DBObject::res->getString("No_Of_Rating") != "0")
        {
            User::instance()->set_rating(stod(DBObject::res->getString("Total_Rating")));
        }
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
    try {
        string command2 = "insert into userlog_table (Username,Lot_Name,Space_No,Start_Time,End_Time) values ('" + userName + "','" + lot + "','" + space_no + "','" + startTime + "','" + endTime + "')";
        int res2 = DBObject::Cstm->executeUpdate(command2);
        if (res2) {
            //Logged new booking
        }
        else {
            //update failed
        }
    }
    catch (sql::SQLException& e) {

        //unknown error
    }
}

bool DBObject::isReserved(string userName)
{
    if (User::instance()->get_status() == "Unreserved")
    {
        return false;
    }
    DBObject::command = "select * from userlog_table where Username= '" + userName + "'"; //checking is this user exist
    try {
        DBObject::res = DBObject::Cstm->executeQuery(command);
        while (DBObject::res->next()) {
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

void DBObject::updateRating(int rating)
{
    //update users set Total_Rating = 3, No_Of_Rating = 1 where username = 'pandy';
    //select* from userlog_table where Lot_Name = 'A' AND Space_No = '20' ORDER BY End_Time DESC;
    DBObject::command = "select * from userlog_table where Lot_Name = '"+ User::instance()->getReservedLot()+"' AND End_Time = '"+User::instance()->get_startTime()+"'";
    try {
        DBObject::res = DBObject::Cstm->executeQuery(command);
        if (DBObject::res->next()) {
            string userName = DBObject::res->getString("Username");
            DBObject::command = "select Total_Rating, No_Of_Rating from users where Username = '" + userName + "'";
            ResultSet* res2 = DBObject::Cstm->executeQuery(command);
            while (res2->next()) {
                float old_rating = res2->getDouble("Total_Rating");
                int old_no_of_rating = res2->getInt("No_Of_Rating");
                DBObject::command = "update users set Total_Rating = ((" + std::to_string(old_rating) + "*" + std::to_string(old_no_of_rating) + ")+" + std::to_string(rating) + ")/(" + std::to_string(old_no_of_rating) + "+1), No_Of_Rating = " + std::to_string(old_no_of_rating) + "+1 where username ='" + userName + "'";
                int i = DBObject::Cstm->executeUpdate(DBObject::command);

                if (i) {
                    // update successfull
                }
            }
        }
    }
    catch (sql::SQLException& e) {

        //couldn't update
    }
}


void DBObject::updateStatus(string status, string username)
{
    //update users set Total_Rating = 3, No_Of_Rating = 1 where username = 'pandy';
    //select* from userlog_table where Lot_Name = 'A' AND Space_No = '20' ORDER BY End_Time DESC;
    DBObject::command = "update users set Status = '"+status+ "' where Username = '"+username+"'";
    try {
        int i = DBObject::Cstm->executeUpdate(DBObject::command);
        if (i) {
            //update successfull
        }
    }
    catch (sql::SQLException& e) {

        //couldn't update
    }
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
