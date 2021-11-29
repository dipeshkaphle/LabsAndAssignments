# Created by Marmik mostly
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

    def insert(self, tableName: str, inputValues: Dict):
        query = "INSERT INTO " + tableName + "("
        query += ",".join(inputValues.keys())
        query += ") VALUES ("
        query += ",".join(["%s"]*len(inputValues))
        query += ")"
        self.cur.execute(query, list(inputValues.values()))
        print("INSERTED")

    def insert_in_order(self, tableName: str, values: List):
        query = "INSERT INTO " + tableName + " VALUES("
        query += ",".join(["%s"] * len(values))
        query += ")"
        self.cur.execute(query, values)

    def update(self, tableName: str, inputValues: Dict, conditonValues: Dict):
        query = "UPDATE " + tableName + " SET "
        query += ",".join(["{} = %s".format(key)
                           for key in inputValues.keys()])
        query += " WHERE "
        query += " and ".join(["{} %s".format(key)
                               for key in conditonValues.keys()])
        self.cur.execute(query, list(inputValues.values()) +
                         list(conditonValues.values()))
        print("\nUPDATED")

    def display(self, tableName: str, conditonValues: Dict):
        self.cur.execute("SELECT * FROM " + tableName + " WHERE " + " and ".join(
            ["{} %s".format(key) for key in conditonValues.keys()]), list(conditonValues.values()))
        self.printCurrentCursor()

    def delete(self, tableName: str, conditonValues: Dict):
        query = "DELETE FROM " + tableName + " WHERE "
        query += " and ".join(["{} %s".format(key)
                               for key in conditonValues.keys()])
        self.cur.execute(query, list(conditonValues.values()))
        print("\nDELETED")

    def displayAll(self, tableName: str):
        print("\nCurrent Table:")
        self.cur.execute("SELECT * FROM " + tableName)
        self.printCurrentCursor()

    def printCurrentCursor(self):
        rows = self.cur.fetchall()
        columns = [desc[0] for desc in self.cur.description]
        header = " | ".join(["{:<15}"]*len(columns))
        if len(rows) == 0:
            return
        print(header.format(*columns))
        print('='*(15 * len(rows[0]) + 3*(len(rows[0])-1)))
        for row in rows:
            print(header.format(*row))

    def executeQuery(self, query: List):
        self.cur.execute(*query)
        self.printCurrentCursor()

    def closeConnection(self):
        self.con.commit()
        self.con.close()


databaseName = "dipesh"
username = "dipesh"
password = ""

database = DatabaseSystem(databaseName, username, password)

createTableQuery = "CREATE TABLE IF NOT EXISTS passengers(seat_no INT PRIMARY KEY, name VARCHAR(255), source VARCHAR(255), destination VARCHAR(255))"

database.createTable("passengers", createTableQuery)


database.insert_in_order('passengers', [3, 'Marmik', 'Delhi', 'Wano'])


def menu():
    print("\n1. Insert")
    print("2. Update With Conditions")
    print("3. Delete With Conditions")
    print("4. Display All")
    print("5. Conditional Display")
    print("6. Exit")
    print("\nEnter your choice: ")
    choice = int(input())
    if choice == 1:
        inputValues = {}
        print("\nEnter Name:", end=" ")
        inputValues['name'] = input()
        print("\nEnter Seat Number:", end=" ")
        inputValues['seat_no'] = int(input())
        print("\nEnter Source:", end=" ")
        inputValues['source'] = input()
        print("\nEnter Destination:", end=" ")
        inputValues['destination'] = input()
        database.insert('passengers', inputValues)
    elif choice == 2:
        inputValues = {}
        conditonValues = {}
        print("\nEnter the conditions: ")
        print("\nEnter Name:", end=" ")
        conditonValues['name = '] = input()
        print("\nEnter the values to be updated: ")
        print("\nEnter Destination:", end=" ")
        inputValues['destination'] = input()
        database.update('passengers', inputValues, conditonValues)
    elif choice == 3:
        conditonValues = {}
        print("\nEnter the conditions: ")
        print("\nEnter Name:", end=" ")
        conditonValues['name = '] = input()
        database.delete('passengers', conditonValues)
    elif choice == 4:
        database.displayAll("passengers")
    elif choice == 5:
        conditonValues = {}
        print("\nEnter the conditions: ")
        print("\nEnter Name:", end=" ")
        conditonValues['name = '] = input()
        print("\nEnter Souce:", end=" ")
        conditonValues['source = '] = input()
        database.display("passengers", conditonValues)
    elif choice == 6:
        database.closeConnection()
        exit()
    else:
        print("\nInvalid choice")
    menu()


database.insert('passengers', {
                'seat_no': 1, 'name': 'Marmik', 'source': 'Delhi', 'destination': 'Mumbai'})
database.insert('passengers', {
                'seat_no': 2, 'name': 'Marmik', 'source': 'Mumbai', 'destination': 'Mumbai'})

database.displayAll("passengers")

menu()
