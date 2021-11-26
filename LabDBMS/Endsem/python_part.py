import psycopg2
from typing import List, Dict


class DatabaseSystem:
    def __init__(self, dbname: str, user: str, password: str):
        self.con = psycopg2.connect(
            host='localhost',
            database=dbname,
            user=user,
            password=password
        )
        self.cur = self.con.cursor()

    def createTable(self, tableName: str, query: str):
        self.cur.execute("DROP TABLE IF EXISTS " + tableName)
        self.cur.execute(query)
        print("\nTable Created")

    def insert(self, tableName: str, values: List, print_=False):
        query = "INSERT INTO " + tableName + " VALUES("
        query += ",".join(["%s"] * len(values))
        query += ")"
        try:
            self.cur.execute(query, values)
            if(print_):
                print(values, "inserted successfully")
        except:
            self.con.rollback()
            print("Error in inserting the values: ", values)

    def find(self, tableName: str, patient_id: int):
        self.cur.execute("SELECT * FROM " + tableName +
                         " WHERE  patient_id= %s", [patient_id])
        self.printCurrentCursor()

    def displayAll(self, tableName: str):
        print("\nCurrent Table:")
        self.cur.execute("SELECT * FROM " + tableName)
        self.printCurrentCursor()

    def printCurrentCursor(self):
        rows = self.cur.fetchall()
        columns = [desc[0] for desc in self.cur.description]
        header = " | ".join(["{:<20}"]*len(columns))
        if len(rows) == 0:
            return
        print(header.format(*columns))
        print('='*(20 * len(rows[0]) + 3*(len(rows[0])-1)))
        for row in rows:
            print(header.format(*row))

    def closeConnection(self):
        self.con.commit()
        self.con.close()


databaseName = "lab_exam"
username = "dipesh"
password = ""

database = DatabaseSystem(databaseName, username, password)

# b. Design a simple database for Patient details Management System using Python and MySQL

# The insert module must be able to accept the patient_id, patient_ name, diagnosis,
# Contact_no, Date_of_admission and store it in the database.
# The find module must be able to accept the Patient_id of the patient and display all the
# details of the corresponding patient.


# Patient Schema
#
# Patient_id - primary key
# Patient_name
# diagnosis
# contact_no
# date_of_admission
#

createTableQuery = '''CREATE TABLE IF NOT EXISTS
    Patients(patient_id INT PRIMARY KEY,
        patient_name VARCHAR(255),
        diagnosis VARCHAR(255),
        contact_no bigint, date_of_admission VARCHAR(20))'''


database.createTable("patients", createTableQuery)

database.insert('patients', [1, 'ram',
                             'alzheimers', '0507797563', '2021-05-23'])
database.insert('patients', [2, 'shyam', 'fever', '0507797563', '2021-05-23'])
database.insert('patients', [3, 'hari', 'cold', '0507797563', '2021-05-23'])
database.insert('patients', [4, 'gokul', 'covid', '0507797563', '2021-04-23'])
database.insert('patients', [5, 'Sita',
                             'cough', '0507797563', '2021-06-23'])
database.insert('patients', [6, 'Laxmi',
                             'jaundice', '0507797563', '2022-05-23'])
database.insert('patients', [7, 'Parvati', 'teeth pain',
                             '0507797563', '2001-05-23'])
database.insert('patients', [8, 'Luffy', 'cancer',
                             '0507797563', '2021-05-23'])
database.insert('patients', [9, 'Dipesh',
                             'kidney problem', '0507797563', '2011-05-23'])
database.insert('patients', [10, 'Zoro', 'headache',
                             '0507797563', '2021-05-19'])


def menu():
    print("1. Insert")
    print("2. Find ")
    print("3. Display All")
    print("4. Close")
    choice = int(input())
    if choice == 1:
        patient_id = int(input("Enter Patient ID: "))
        patient_name = input("Enter Patient Name: ")
        diagnosis = input("Enter diagnosis: ")

        contact_no = int(input("Enter Contact No: "))
        date_of_admission = input("Enter Date of Admission: ")
        database.insert('patients', [
                        patient_id, patient_name, diagnosis, contact_no, date_of_admission], True)
        print()
        print()
    elif choice == 2:
        patient_id = int(input("Enter patient id: "))
        database.find("patients", patient_id)
        print()
        print()
    elif choice == 3:
        database.displayAll('patients')
        print()
        print()
    elif choice == 4:
        database.closeConnection()
        exit()
    else:
        print("\nInvalid choice")
        print()
        print()
    menu()


menu()
