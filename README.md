# restaurant-simulatio
RESTAURANT DESIGN

Purpose of the program is find the total cost depends on the
customers order.
In my program assume that there are five empty tables and 
no limitations of the one table's customers and orders.
There are some dishes and their ingredients in restaurants menu
in menu.txt. Dishes available only if ingredients exist.
There are ingredients and their types and amounts and
also their prices in stock.txt file.
There are orders for each table with the number of orders then
orders in order.txt file.
Assume that checkout will be calculated as cost of dishes plus tax plus tip.
Tax is %8 of cost of dishes.
Tip is %15 of cost of dishes.
Example screenshot : ...

Coding Mechanishm (OOP)

I used polymorphism in this project. There is a class that keeps
ingredients. Then there are three child class which are child of
ingredients type1, type2 and type3.
Program first reads stock file and all items keeps in linked 
list in ingredients form.
Then reads the order file. rest_book function check the order
if it is available in menu.
class Items :
keep name of ingredient and keep type.
Include 4 virtual functions for child classes.
class type1 :
keep grams type.
construct it first with name, type, amount and price per gram.
class type2:
keep unit.
construct it first with name, type, amount and price.
class type3:
keep mililitres.
construct it first with name, type, amount and price per mililitre.
float memory -> purpose of this function is update the stock.
Then it returns the cost of using ingredients.
If no ingredients found then returns -1.
bool scannList -> pupose of this function check the stock and
says the program there is enough ingredient or no enough 
ingredient. Returns true of false.
float rest_book -> purpose of this function scann the menu
and tells the customer if order is exist or not.
