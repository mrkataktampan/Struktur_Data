#include <iostream>
#include <mysql/mysql.h>
#include <sstream>
#include <limits>

using namespace std;

const char* host = "127.0.0.1";
const char* user = "root";
const char* password = "izaz258";
const char* dbname = "cpp_crud";
unsigned int port = 31235;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* connection = mysql_init(0);
    if (connection) {
        connection = mysql_real_connect(connection, host, user, password, dbname, port, unixsocket, clientflag);
        if (connection) {
            cout << "Successfully connected to the database." << endl;
        } else {
            cerr << "Connection failed: " << mysql_error(connection) << endl;
        }
    } else {
        cerr << "mysql_init failed" << endl;
    }
    return connection;
}

void register_user(const string& username, const string& password, const string& role) {
    MYSQL* connection = connect_db();
    if (connection) {
        string query = "INSERT INTO admin (username, password, role) VALUES ('" + username + "', '" + password + "', '" + role + "')";
        if (mysql_query(connection, query.c_str())) {
            cerr << "INSERT failed: " << mysql_error(connection) << endl;
        } else {
            cout << "User successfully registered." << endl;
        }
        mysql_close(connection);
    }
}

bool admin_login(const string& username, const string& password, int& failed_attempts) {
    MYSQL* connection = connect_db();
    if (connection) {
        string query = "SELECT password FROM admin WHERE username = '" + username + "' AND role = 'admin'";
        if (mysql_query(connection, query.c_str())) {
            cerr << "SELECT failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return false;
        }

        MYSQL_RES* result = mysql_store_result(connection);
        if (result == nullptr) {
            cerr << "mysql_store_result failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return false;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0] == password) {  // assuming password is at index 0
            cout << "Admin login successful." << endl;
            failed_attempts = 0;
            mysql_free_result(result);
            mysql_close(connection);
            return true;
        } else {
            failed_attempts++;
            cout << "Login failed: Invalid username or password. Attempt " << failed_attempts << " of 3." << endl;
            if (failed_attempts >= 3) {
                mysql_free_result(result);
                mysql_close(connection);
                cout << "Maximum login attempts reached. Exiting..." << endl;
                exit(1);
            }
        }

        mysql_free_result(result);
        mysql_close(connection);
    }
    return false;
}

bool user_login(const string& username, const string& password, int& failed_attempts) {
    MYSQL* connection = connect_db();
    if (connection) {
        string query = "SELECT password FROM admin WHERE username = '" + username + "' AND role = 'user'";
        if (mysql_query(connection, query.c_str())) {
            cerr << "SELECT failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return false;
        }

        MYSQL_RES* result = mysql_store_result(connection);
        if (result == nullptr) {
            cerr << "mysql_store_result failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return false;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0] == password) {  // assuming password is at index 0
            cout << "User login successful." << endl;
            failed_attempts = 0;
            mysql_free_result(result);
            mysql_close(connection);
            return true;
        } else {
            failed_attempts++;
            cout << "Login failed: Invalid username or password. Attempt " << failed_attempts << " of 3." << endl;
            if (failed_attempts >= 3) {
                mysql_free_result(result);
                mysql_close(connection);
                cout << "Maximum login attempts reached. Exiting..." << endl;
                exit(1);
            }
        }

        mysql_free_result(result);
        mysql_close(connection);
    }
    return false;
}

void consign_sale(const string& item_name, double price, int quantity, const string& description, const string& seller) {
    MYSQL* connection = connect_db();
    if (connection) {
        stringstream query;
        query << "INSERT INTO users (item_name, price, quantity, description, seller) VALUES ('"
              << item_name << "', " << price << ", " << quantity << ", '" << description << "', '" << seller << "')";
        if (mysql_query(connection, query.str().c_str())) {
            cerr << "INSERT failed: " << mysql_error(connection) << endl;
        } else {
            cout << "Item successfully consigned." << endl;
        }
        mysql_close(connection);
    }
}

void buy_item(int item_id, int quantity) {
    MYSQL* connection = connect_db();
    if (connection) {
        stringstream query;
        query << "UPDATE users SET quantity = quantity - " << quantity << " WHERE id = " << item_id << " AND quantity >= " << quantity;
        if (mysql_query(connection, query.str().c_str())) {
            cerr << "UPDATE failed: " << mysql_error(connection) << endl;
        } else {
            if (mysql_affected_rows(connection) > 0) {
                cout << "Item successfully purchased." << endl;
            } else {
                cout << "Insufficient item quantity." << endl;
            }
        }
        mysql_close(connection);
    }
}

void display_items() {
    MYSQL* connection = connect_db();
    if (connection) {
        if (mysql_query(connection, "SELECT * FROM users")) {
            cerr << "SELECT failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return;
        }

        MYSQL_RES* result = mysql_store_result(connection);
        if (result == nullptr) {
            cerr << "mysql_store_result failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            cout << "ID: " << row[0] << ", Item Name: " << row[1] << ", Price: " << row[2]
                 << ", Quantity: " << row[3] << ", Description: " << row[4] << ", Seller: " << row[5] << endl;
        }

        mysql_free_result(result);
        mysql_close(connection);
    }
}

void update_item_data(int item_id, const string& item_name, double price, int quantity, const string& description) {
    MYSQL* connection = connect_db();
    if (connection) {
        stringstream query;
        query << "UPDATE users SET item_name = '" << item_name << "', price = " << price
              << ", quantity = " << quantity << ", description = '" << description
              << "' WHERE id = " << item_id;
        if (mysql_query(connection, query.str().c_str())) {
            cerr << "UPDATE failed: " << mysql_error(connection) << endl;
        } else {
            cout << "Item data successfully updated." << endl;
        }
        mysql_close(connection);
    }
}

bool get_users() {
    MYSQL* connection = connect_db();
    if (connection) {
        if (mysql_query(connection, "SELECT * FROM admin")) {
            cerr << "SELECT failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return false;
        }

        MYSQL_RES* result = mysql_store_result(connection);
        if (result == nullptr) {
            cerr << "mysql_store_result failed: " << mysql_error(connection) << endl;
            mysql_close(connection);
            return false;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            cout << "ID: " << row[0] << ", Username: " << row[1] << ", Role: " << row[3] << endl;
        }

        mysql_free_result(result);
        mysql_close(connection);
    }
    return true;
}

void delete_user(int user_id) {
    MYSQL* connection = connect_db();
    if (connection) {
        stringstream query;
        query << "DELETE FROM admin WHERE id = " << user_id;
        if (mysql_query(connection, query.str().c_str())) {
            cerr << "DELETE failed: " << mysql_error(connection) << endl;
        } else {
            cout << "User successfully deleted." << endl;
        }
        mysql_close(connection);
    }
}

void delete_item(int item_id) {
    MYSQL* connection = connect_db();
    if (connection) {
        stringstream query;
        query << "DELETE FROM users WHERE id = " << item_id;
        if (mysql_query(connection, query.str().c_str())) {
            cerr << "DELETE failed: " << mysql_error(connection) << endl;
        } else {
            cout << "Item successfully deleted." << endl;
        }
        mysql_close(connection);
    }
}

void user_menu(const string& username) {
    while (true) {
        cout << "==============================\n";
        cout << "|      Aplikasi TOSERBA      |\n";
        cout << "==============================\n";
        cout << "| 1. Sell Item               |\n";
        cout << "| 2. Buy Item                |\n";
        cout << "| 3. Display All Items       |\n";
        cout << "| 4. Update Item Data        |\n";
        cout << "| 5. Delete Item             |\n";
        cout << "| 6. Logout                  |\n";
        cout << "==============================\n";
        cout << " Masukkan Pilihan Anda: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string item_name, description;
                double price;
                int quantity;
                cout << "Enter item name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear input buffer
                getline(cin, item_name);
                cout << "Enter price: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear input buffer
                cout << "Enter description: ";
                getline(cin, description);
                consign_sale(item_name, price, quantity, description, username);
                break;
            }
            case 2: {
                int item_id, quantity;
                cout << "Enter item ID to buy: ";
                cin >> item_id;
                cout << "Enter quantity: ";
                cin >> quantity;
                buy_item(item_id, quantity);
                break;
            }
            case 3:
                display_items();
                break;
            case 4: {
                int item_id;
                string item_name, description;
                double price;
                int quantity;
                cout << "Enter item ID to update: ";
                cin >> item_id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear input buffer
                cout << "Enter new item name: ";
                getline(cin, item_name);
                cout << "Enter new price: ";
                cin >> price;
                cout << "Enter new quantity: ";
                cin >> quantity;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear input buffer
                cout << "Enter new description: ";
                getline(cin, description);
                update_item_data(item_id, item_name, price, quantity, description);
                break;
            }
            case 5: {
                int item_id;
                cout << "Enter item ID to delete: ";
                cin >> item_id;
                delete_item(item_id);
                break;
            }
            case 6:
                cout << "Successfully exited." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void admin_menu() {
    while (true) {
        cout << "==============================\n";
        cout << "|     Menu Administrator     |\n";
        cout << "==============================\n";
        cout << "| 1. View All Users          |\n";
        cout << "| 2. Delete User             |\n";
        cout << "| 3. Display All Items       |\n";
        cout << "| 4. Update Item Data        |\n";
        cout << "| 5. Delete Item             |\n";
        cout << "| 6. Logout                  |\n";
        cout << "==============================\n";
        cout << " Masukkan Pilihan Anda: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (!get_users()) {
                    cout << "No user data available. Press Enter to continue...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear input buffer
                    cin.get();  // wait for user to press Enter
                }
                break;
            case 2: {
                int user_id;
                cout << "Enter user ID to delete: ";
                cin >> user_id;
                delete_user(user_id);
                break;
            }
            case 3:
                display_items();
                break;
            case 4: {
                int item_id;
                string item_name, description;
                double price;
                int quantity;
                cout << "Enter item ID to update: ";
                cin >> item_id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear input buffer
                cout << "Enter new item name: ";
                getline(cin, item_name);
                cout << "Enter new price: ";
                cin >> price;
                cout << "Enter new quantity: ";
                cin >> quantity;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear input buffer
                cout << "Enter new description: ";
                getline(cin, description);
                update_item_data(item_id, item_name, price, quantity, description);
                break;
            }
            case 5: {
                int item_id;
                cout << "Enter item ID to delete: ";
                cin >> item_id;
                delete_item(item_id);
                break;
            }
            case 6:
                cout << "Successfully exited." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    int failed_attempts = 0;
    string username, password, role;

    while (true) {
        cout << "==========================\n";
        cout << "|    Aplikasi TOSERBA    |\n";
        cout << "==========================\n";
        cout << "| 1. Admin Login         |\n";
        cout << "| 2. User Login          |\n";
        cout << "| 3. Register            |\n";
        cout << "| 4. Exit                |\n";
        cout << "==========================\n";
        cout << "Masukkan Pilihan Anda: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "==============================\n";
                cout << "|      Aplikasi TOSERBA      |\n";
                cout << "==============================\n";
                cout << " Masukkan admin username: ";
                cin >> username;
                cout << " Masukkan admin password: ";
                cin >> password;
                if (admin_login(username, password, failed_attempts)) {
                    admin_menu();
                }
                break;
            }
            case 2: {
                cout << "==============================\n";
                cout << "|      Aplikasi TOSERBA      |\n";
                cout << "==============================\n";
                cout << " Masukkan username: ";
                cin >> username;
                cout << " Masukkan password: ";
                cin >> password;
                if (user_login(username, password, failed_attempts)) {
                    user_menu(username);
                }
                break;
            }
            case 3: {
                cout << "==============================\n";
                cout << "|      Aplikasi TOSERBA      |\n";
                cout << "==============================\n";
                cout << " Masukkan username baru: ";
                cin >> username;
                cout << " Masukkan password baru: ";
                cin >> password;
                cout << "Enter role (admin/user): ";
                cin >> role;
                register_user(username, password, role);
                break;
            }
            case 4:
                cout << "===============================================\n";
                cout << "| Terima Kasih Telah Menggunakan Aplikasi Ini |" << endl;
                cout << "===============================================\n";
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
