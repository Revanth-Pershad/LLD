/*
    **High-level modules should not depend on low-level modules. Both should depend on abstractions.**

- Use **interfaces** instead of concrete classes.
*/

// Bad Example
class MySQLDatabase {
public:
    void saveData() {
        // Save data in MySQL
    }
};

class Application {
private:
    MySQLDatabase db;  // Tightly coupled
public:
    void save() {
        db.saveData();
    }
};

/*
    Now in the future if we want to use a PostGreSqlclass we cannot use it since the Application class is tightly coupled with the MySqlDatabase
    so instead we define a parent interface for both of them and use the interfact rather than the classes.
*/

// Good Example
class Database {
public:
    virtual void saveData() = 0;
};

class MySQLDatabase : public Database {
public:
    void saveData() override {
        // Save data in MySQL
    }
};

class PostgreSQLDatabase : public Database {
public:
    void saveData() override {
        // Save data in PostgreSQL
    }
};

class Application {
private:
    Database* db;
public:
    Application(Database* database) : db(database) {}

    void save() {
        db->saveData();
    }
};