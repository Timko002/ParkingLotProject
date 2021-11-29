#include "DBObject.h"

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
        try {
            DBObject::command = "INSERT INTO users (Username, Password) VALUES ('" + userName + "','" + pass + "')"; //checking is this user exist
            DBObject::res = DBObject::Cstm->executeQuery(command);
        }
        catch (sql::SQLException& e) {

            //Is this a dll error?
        }
    }
}
