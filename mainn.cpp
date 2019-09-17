#include <iostream>
#include <fstream>
#include <list>  //FOR THE ready doublylinkedlist  
#include <sstream> //FOR THE istringstream

using namespace std;

//----------------------CLASS DEFINITIONS BEGIN ----------------------------
class Items{  //BASE CLASS
    string nameOfItem;  //NAME OF ITEM
    int typeOfItem;        //TYPE OF ITEM
public:
    string& keepName()    //RETURNS THE NAME OF STRING
	{return nameOfItem;}
    int keepType()
	{return typeOfItem;}
    virtual float Cost(int) = 0;  //POLYMORPHISM STRUCTURES BEGIN
    virtual int keepItemCount() = 0; 
    virtual void setItemCount(int ) = 0;
    virtual float calcPrice() = 0;
    Items(string &nameOfItem, int typeOfItem): nameOfItem(nameOfItem), typeOfItem(typeOfItem){} //CONSTRUCTOR INHERITANCE 
};
//----------------DERIVED CLASSES BEGIN----------------------------
class Type1 : public Items{
    int grams;
    float priceGrams;
public:
	//CONSTRUCTOR WITH INHERITANCE
    Type1(string &nameOfItem, int typeOfItem, int numberOf, float price): Items(nameOfItem, typeOfItem), grams(numberOf), priceGrams(price){}
    //THESE FOUR FUNCTIONS VIRTUAL TOO FOR POLYMORPHISM
	int keepItemCount()
	{return grams;}   //KEEP THE WEIGHT OF ITEM           
    void setItemCount(int remainItem)
	{grams = remainItem;}  //KEEP THE REMAIN ITEM BECAUSE OF THE ORDER 
    float calcPrice() // CALCULATE THE PRÝCE FOR EACH GRAMS 
	{return priceGrams;}
    float Cost(int numberOf)  //THEN FIND THE FINAL COST
	{return (numberOf * priceGrams);}
};

class Type2 : public Items{ //DERIVED FROM ITEM CLASS
    int quantity;  //bir adet veya iki adet = one unit
    float perQuantity;  //price per unit
public:
	//CONSTRUCTOR WITH INHERITANCE
    Type2(string &nameOfItem, int typeOfItem, int numberOf, float price):Items(nameOfItem, typeOfItem), quantity(numberOf), perQuantity(price){}
    //THESE FOUR FUNCTIONS VIRTUAL TOO FOR POLYMORPHISM
    int keepItemCount() //KEEP THE QUANTITY OF ITEM
	{return quantity;}
    void setItemCount(int remainItem) //KEEP THE REMAIN ITEM BECAUSE OF THE ORDER 
	{quantity = remainItem;}
    float calcPrice() // CALCULATE THE PRÝCE FOR PER QUANTITY
	{return perQuantity;}
    float Cost(int numberOf) //THEN FIND THE FINAL COST
	{return numberOf * perQuantity;}
};

class Type3 : public Items{
    int mili;
    float perMili;
public:
	//CONSTRUCTOR WITH INHERITANCE
    Type3(string &nameOfItem, int typeOfItem, int numberOf, float price):Items(nameOfItem, typeOfItem), mili(numberOf), perMili(price){}
    //THESE FOUR FUNCTIONS VIRTUAL TOO FOR POLYMORPHISM
    int keepItemCount() //KEEP THE QUANTITY OF ITEM
	{return mili;}
    void setItemCount(int remainItem) //KEEP THE REMAIN ITEM BECAUSE OF THE ORDER 
	{mili = remainItem;}
    float calcPrice() // CALCULATE THE PRÝCE FOR PER MILILITRE
	{return perMili;}
    float Cost(int numberOf) //THEN FIND THE FINAL COST
	{return numberOf * perMili;}
};

//--------------------END OF THE CLASS DEFINITIONS--------------------------------------------
//--------------BEGINNING OF THE MAIN PARTS --------------------------
float memory(list<Items*> List, string &things, int counter) //STORE THE ITEMS FUNCTION 
{
	int not_success = -1;
    list<Items*>::iterator traverse;  //DOUBLY LINKED LIST ITERATOR
    traverse = List.begin();  //BEGININNIG OF THE LIST 
    while (traverse != List.end()) { //SCAN THE LIST (TRAVERSE ) 
        if(things == (*traverse)->keepName()){  //if the things equal to from list 
            (*traverse)->setItemCount((*traverse)->keepItemCount() - counter);
            return (*traverse)->Cost(counter);
        }
        traverse++;  //INCREASE THE POINTER 
    }
    return not_success; //not success 
}

bool scannList(list<Items*> List, string &things, int counter) //FOR THE FIND THE ITEM FUNCTION 
{
	int error = 0;
    list<Items*>::iterator traverse; //DPUBLY LINKED LIST ITERATOR 
    traverse = List.begin(); //STARTING POINT OF THE LIST 
	while (traverse != List.end()) { //SCAN THEE LIST TIL THE END 
        if (things == (*traverse)->keepName() && ((*traverse)->keepItemCount() >= counter )){ // IF THE ITEM NAME IS MATERIAL AND THE ITEM EXIST IN THE LIST 
        	return true; //SUCCESS 
		} 
        traverse++; //INCREASE THE POINTER 
    }  
    return false; // NO SUCCESS 
}

float rest_book(list<Items*> &List, string &yeniSiparis){
    string bos; //EMPTY STRING 
	string row; // LINE NUMBR
	string order; //ORDER
	string item; //ITEM 
	string numberOf; //ML - GRAM  - NUMBER
	string thing; // MATERIAL 
    int counter = 1; //FOR THE ITEM COUNT 
    char bosKarakter; // ANY EMPTY CHARACTER 
    int checker = 1; //CHECKER THAT CHECK THE ORDER IS EXIST 
    float finalCost = 0; //KEEP THE FINAL COST 
    int succeed = -1;
    //----------------END OF THE VARIABLE DEFINITION -----------------
    ifstream menuFile("menu.txt"); //READ THE MENU FILE 
    if(menuFile.is_open()){
        getline(menuFile, bos); //FIRST LINE - NAME - INGREDIENTS 
        while(getline(menuFile, row)){ //THEN READ THE MENU BY LINE 
            istringstream ww(row);
            getline(ww, order, '\t'); // SEPERATE BY TABS 
            if(order == yeniSiparis){
                getline (ww, bos, '\r'); //carriage return character 
                istringstream ww1(bos);
                if(bos == "N/A"){ // IF THERE IS NO INGREDIENT
                    thing = order; // THAT IS THE ORDER 
                    if (!scannList(List, thing, counter)){
                    	checker = 0; // ORDER IS not EXIST 
					} 
                }
                else { // IF THERE IS INGREDIENT THAT MEAN TYPE1 TYPE2 OR TYPE3 
                    while (getline(ww1, item, ',')) {
                        istringstream ww2(item);
                        ww2 >> counter >> numberOf;
                        if (numberOf == "ml" || numberOf == "gram") {
                            ww2 >> noskipws >> bosKarakter; //noskipws MEANS THAT CONSIDER THE SPACE 
                            getline(ww2, thing);;
                        } else {
                            thing = numberOf;
                        }
                        if (!scannList(List, thing, counter)) {
                        	checker = 0; //IF THE CHECKER IS 0 , IT MEANS THERE IS NO ENOUGH ITEM
						}
                    }
                }
                if(checker) { //CHECKER CONTROL 
                    istringstream ww3(bos); //CREATE EMPTY
                    if(bos == "N/A"){ //IF EMPTY IS NO INGREDIENT
                        thing = order; //ORDER IS THE THING DIIRECTLY
                        finalCost += memory(List, thing, counter);
                    }
                    else{ //IF HAVE INGREDIENTS 
                        while (getline(ww3, item, ',')) { //TAKE CARE THE KOMMA 
                            istringstream ww2(item);
                            ww2 >> counter >> numberOf;
                            if (numberOf == "ml" || numberOf == "gram") { // TYPE 1 OR TYPE 3 
                                ww2 >> noskipws >> bosKarakter; //noskipws MEANS THAT CONSIDER THE SPACE 
                                getline(ww2, thing);
                            } else {
                                thing = numberOf;
                            }
                            finalCost += memory(List, thing, counter);
                        }
                    }
                    return finalCost; //RETURN THE COST 
                }else {
					cout << "We don't have enough " << order << endl; //IF THERE IS NO ITEM ENOUGH 
				}
            }
        }
    }
    menuFile.close(); //END OF THE READ MENU FILE
    return succeed;
}

void itemLister(list<Items*> List) //ITEMS LIST
{
    ofstream Lister;  //FOR WRITE THE STOCKK
    Lister.open("stock.txt");
    list<Items*>::iterator traverse;
    traverse = List.begin();
    Lister << "Name" << "\t" << "Type" << "\t" << "ItemCount" << "\t" << "Price\n" ;
    while (traverse != List.end()) {
        Lister << (*traverse)->keepName() << "\t" << (*traverse)->keepType() << "\t" << (*traverse)->keepItemCount() << "\t" << (*traverse)->calcPrice() << endl;
        traverse++;
    }
    Lister.close();
}
//MAIN STARTS
int main(){
	int type_1 = 1, type_2 = 2, type_3 = 3;
    string item_name;   //keep item names
	string row;			//row that how many lines count
	string temp;    //TEMP STRING
    int get_type;  //type of items
	int numberOfItem;  //number of items in stock
    float perPrice;  // price
    string table_no;  //keep table no
	string order;  //keep order string type 
	string order_no;   //string order no 
	string line_no;   
	//NUMBER OF ORDERS AND LINES
    int int_order_no = 0;
	int int_line_no = 0;
	//PAYMENTS 
    float Cost;
	float ucret;
	float bahsis;
	float vergi;
	float toplam = 0;
    list<Items*>Stok;  //linked list of items
    
	//READ OF THE STOCK FILE 
	ifstream stockFile("stock.txt");
    if (stockFile.is_open()) {        
        getline(stockFile, temp); //KEEP THE STRINGS OF THE TYPES -- NAME --TYPE -- ITEMCOUNT..
        while(getline(stockFile, row)) { //READ TILL THE END
            istringstream ww(row); 
            getline(ww, item_name, '\t'); // READ ONE LINE WITH 'TAB UNIT'
            ww >> get_type >> numberOfItem >> perPrice; //KEEP INFORMATIONS PER ITEM
            //THEN USING THE LIST FUNCTIONS PUSH THE STOK LIST
            //CHECK THE TYPES OF THE ITEMS
            switch(get_type){
            	case 1:
            		Stok.push_back(new Type1(item_name, type_1, numberOfItem, perPrice)); //PUSH THE LINKED LIST 
            		break;
            	case 2:
            		Stok.push_back(new Type2(item_name, type_2, numberOfItem, perPrice)); //PUSH THE LINKED LIST 
            	    break;
            	case 3:
            		Stok.push_back(new Type3(item_name, type_3, numberOfItem, perPrice)); //PUSH THE LINKED LIST 
            	    break;
            	default:
            		break;        
			}
        }
    }
    stockFile.close();
    //---------------------------END OF THE READ STOCK FILE-----------------------------
    //----------------READ ORDER FILE --------------------------
    ifstream orderFile("order.txt");
    if (orderFile.is_open()) {
        while (getline(orderFile, row)) {
            ucret = 0;
			bahsis = 0;
			vergi = 0;
            istringstream table(row); //FOR EACH TABLE 
            getline(table, table_no, '\r'); //GET FIRST TABLE
            getline(orderFile, line_no);  //GET NUMBER OF ORDER
            istringstream mm(line_no); //to lýine number 
            mm >> int_line_no; // get the line 
            cout << table_no << " ordered:"<< endl;
            //------------------GET THE ORDER ------------------------
            for (int m = 0; m < int_line_no; m++) {
                Cost = 0;
                getline(orderFile,row);
                istringstream ww2(row);
                getline(ww2, order_no, ' ');
                istringstream ww3(order_no);
                ww3 >> int_order_no;
                getline(ww2, order, '\r');
                for(int k = 0; k < int_order_no; k++){
                	Cost +=  rest_book(Stok, order);
				}
                if(Cost < 0 ); //IF COST < 0 NOTHING TO DO THAT 
                else {
                    cout << int_order_no << " " << order <<" cost: " << Cost << endl  ;
                    ucret += Cost;
                }
            }
            bahsis = ucret * (0.15);  //CALCULATE TIP 
            vergi = ucret * (0.08); //CALCULATE COST            
            cout << "Tip is " << bahsis << endl;
            toplam = ucret + vergi + bahsis;
            cout << "Total cost: " << toplam << " TL\n**************************" << endl;
        }
    }
    orderFile.close();
    itemLister(Stok); //KEEP THE STOCK
    return 0;
}
