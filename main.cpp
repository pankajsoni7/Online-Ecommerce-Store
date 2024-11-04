//----------------PANKAJ DSA PROJECT-------------------//



#include <bits/stdc++.h>
#define size 50
#define V 11
#define V1 6

using namespace std;
struct user
{
    string name;
    string product;
    int quantity;
    double bill;

    user() {}

    user(string name, string product, int quantity, double bill)
    {
        this->name = name;
        this->product = product;
        this->quantity = quantity;
        this->bill = bill;
    }
};


struct deliveryUser
{
    user nUser;
    string address;
    double deliveryCharges;
    int distanceDelivery;
    deliveryUser *next = NULL;

    deliveryUser(string name, string product, int quantity, double bill, string address, double deliveryCharges, int distanceDelivery)
    {
        this->nUser = user(name, product, quantity, bill);
        this->address = address;
        this->deliveryCharges = deliveryCharges;
        this->distanceDelivery = distanceDelivery;
    }
};


struct Shop
{
    string name;
    string *product;
    int *price;
    string address;
    deliveryUser *nextdeliveryUser;
};


Shop* shop=NULL;
string addressF;
int dist[V];
int distanceP[V1];
int optionDelivery = -999;
int optionDelivery1 = -999;
deliveryUser *currentdeliveryUser = NULL;

//---------------------------------------------------------------------------------------------------------------------
//Take Away Users**********************************************

struct takeAway
{
    string name;
    string product;
    int quantity;
    double bill;
    int orderId;
    takeAway *left;
    takeAway *right;
    
    //takeAwayfromStore *next = NULL;

    takeAway(string name, string product, int quantity, double bill, int orderId)
    {
        this->name=name;
		this->product = product;
        this->quantity = quantity;
        this->bill = bill;
        this->orderId=orderId;
        this->left = NULL;
        this->right = NULL;
    }
};

takeAway *root = NULL; 

void display(takeAway *root)
{
	cout <<"\n----------------------------------"<< endl;
    cout << "Name :" << root->name << endl;
    cout << "product :" << root->product << endl;
    cout << "Quantity : " << root->quantity << endl;
    cout << "Bill : " << root->bill << endl;
    cout << "Order ID: " << root->orderId << endl;
    cout <<"-----------------------------------\n"<< endl;
}

takeAway *displayTakeAway(takeAway *root)
{

    if (root)
    {
        displayTakeAway(root->left);
        display(root); 
        displayTakeAway(root->right);
    }

    return root;
}

// isEmpty or not
int isEmpty(takeAway *root)
{
    return root == NULL;
}


// Height of takeAway tree
int height(takeAway* root) {
	if (root == NULL)
      return -1;
    else {
      int leftH = height(root -> left);
      int rightH = height(root -> right);

    return (1+max(leftH , rightH));
	}
}

// Balance Factor for each takeAway node
int balanceFactor(takeAway *root)
{
    if (!root)
        return 0;

    return height(root->left) - height(root->right);
}

// Maximum of two integers as a helper function for height
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Searching in takeAway tree

takeAway *search(takeAway *root, int id)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->orderId == id)
    {
        return root;
    }
    else if (root->orderId < id)
    {
        return search(root->right, id);
    }
    else if (root->orderId > id)
    {
        return search(root->left, id);
    }

    return root;
}

// Balancing the takeAway's Tree thorugh AVL Rotations

// LL Rotation
takeAway *LLRotation(takeAway *root)
{
    takeAway *x = root->left;
    takeAway *temp = x->right;

    x->right = root;
    root->left = temp;

    root = x;

    return x;
}

// RR Rotation
takeAway *RRRotation(takeAway *root)
{

    takeAway *x = root->right;
    takeAway *temp = x->left;

    x->left = root;
    root->right = temp;

    root = x;

    return x;
}

// LR Rotation
takeAway *LRRotation(takeAway *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// RL Rotation
takeAway *RLRotation(takeAway *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

//  INSERTION in takeAway Tree

takeAway *insertion(string name, int quantity, string product, double bill, int orderId, takeAway *root)
{
    takeAway *newNode = new takeAway(name,  product, quantity, bill, orderId);

    if (root == NULL)
    {
        root = newNode;
    }

    else if (root->orderId > newNode->orderId)
    {
        root->left = insertion(name, quantity, product, bill, orderId, root->left);
    }
    else if (root->orderId < newNode->orderId)
    {
        root->right = insertion(name, quantity, product, bill, orderId, root->right);
    }

    else
    {
        cout << "No duplicates Values are Allowed " << endl;
        return root;
    }

    int bf = balanceFactor(root);

    if (bf == 2)
    {
        // LL
        if (root->left->orderId > newNode->orderId)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->orderId < newNode->orderId)
        {
            return LRRotation(root);
        }
    }
    else if (bf == -2)
    {
        // RR
        if (root->right->orderId < newNode->orderId)
        {
            return RRRotation(root);
        }

        // RL
        if (root->right->orderId > newNode->orderId)
        {
            return RLRotation(root);
        }
    }

    return root; // in case there is no need of rotation
}

takeAway * minValue(takeAway *root) {
    takeAway *current = root;
    while (current-> left != NULL) {
      current = current -> left;
    }
    return current;
  }

takeAway *deleteNode(takeAway *root, int orderId)
{
    if (root == NULL)
        return root;
    else if (orderId < root->orderId)
        root->left = deleteNode(root->left, orderId);
    else if (orderId > root->orderId)
        root->right = deleteNode(root->right, orderId);
    else {
      if (root-> left == NULL) {
        takeAway* temp = root-> right;
        delete root;
        return temp;
      } 
	  else if (root-> right == NULL) {
        takeAway* temp = root-> left;
        delete root;
        return temp;
      } 
      
	  else {
        takeAway * temp = minValue(root-> right);
        root-> orderId = temp -> orderId;
        root-> right = deleteNode(root-> right, temp-> orderId );
      }
    }

    // getting the balance factor
    int balance = balanceFactor(root);

    // Rotation Cases
    // LEFT LEFT CASE
    if (balance > 1 && orderId < root->left->orderId)
        return LLRotation(root);

    // LEFT RIGHT CASE
    if (balance > 1 && orderId > root->left->orderId)
    {
        root->left = LLRotation(root->left);
        return LRRotation(root);
    }

    // RIHGT RIGHT CASE
    if (balance < -1 && orderId > root->right->orderId)
        return RRRotation(root);

    // RIGHT LEFT CASE
    if (balance < -1 && orderId < root->right->orderId)
    {
        return RLRotation(root);
    }

    return root;
}





//-----------------------------------------------------------------------------------------------------------------------
void placeOrderHomeDeliveryCustomer(string name, string product, int quantity, double bill, string address, int deliveryCharges, int distanceDelivery)
{

    currentdeliveryUser=new deliveryUser(name, product, quantity, bill, address, deliveryCharges, distanceDelivery);
    
    if (shop->nextdeliveryUser == NULL)
    {
        // if first insert in front
        shop->nextdeliveryUser= currentdeliveryUser;
    }
    else
    {
        // finding the last Node
        deliveryUser *temp = shop->nextdeliveryUser;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentdeliveryUser;
        currentdeliveryUser->next = NULL;
    }
    
   	cout << "\n**Order Details";
    cout << "\n Customer Name : " << name << "\n Order name : " << product << "\n Quantity : " << quantity << "\n Total bill : " << bill;
    cout << "\n Address : " << address << "\n Distance in km : " << distanceDelivery <<"\n Delivery charges : " << deliveryCharges << endl;
}


void displayAllOrdersHomeDeliveryCustomers()
{
    if (shop->nextdeliveryUser == NULL)
    {
        cout << "There is no Order for Home Delivery Customer till yet" << endl;
    }
    else
    {
        deliveryUser *traversal = shop->nextdeliveryUser;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Home Delivery for : " << traversal->nUser.name << endl;
            cout << "Product Name : " << traversal->nUser.product << endl;
            cout << "Quantity : " << traversal->nUser.quantity << endl;
            cout << "Delivery Distance : " << traversal->deliveryCharges << "KM"<<endl;
            cout << "Delivery Charges : " << traversal->distanceDelivery << endl;
            cout << "Bill : " << traversal->nUser.bill << " RS/_" << endl;
            cout << "Delivery Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
    
}





//-----------------------------------------------------------------------------------

int minDistance(int dist[], bool visited[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}



void dijkstra(int graph[V][V], int dist[], int src)
{
    bool visited[V]; 

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);

        visited[u] = true;
        
        for (int v = 0; v < V; v++)

            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                	dist[v] = dist[u] + graph[u][v];
    }
}

//-----------------------------------------------------------------------------------

int minKey(int distanceP[], bool visitedP[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V1; v++)
		if (visitedP[v] == false && distanceP[v] < min)
			min = distanceP[v], min_index = v;

	return min_index;
}

void printMST(int parent[], int graph[V1][V1])
{
	cout << "Edge \tWeight\n";
	for (int i = 1; i < V1; i++)
		cout << parent[i] << " - " << i << " \t"
			<< graph[i][parent[i]] << " \n";
}

void prims(int graph[V1][V1], int distanceP[])
{
	int parent[V1];
	bool visitedP[V1];

	for (int i = 0; i < V1; i++)
		distanceP[i] = INT_MAX, visitedP[i] = false;

	distanceP[0] = 0;
	parent[0] = -1; 

	for (int count = 0; count < V1 - 1; count++) {

		int u = minKey(distanceP, visitedP);

		visitedP[u] = true;

		for (int v = 0; v < V1; v++)

			if (graph[u][v] && visitedP[v] == false && graph[u][v] < distanceP[v])
				parent[v] = u, distanceP[v] = graph[u][v];
	}

}






//-----------------------------------------------------------------------------------


string CityName[] = {"Store Location", "Mumbai", "Delhi", "Bangalore", "Jaipur", "Bhopal", "Goa", "Ahmedabad", "Kolkata", "Srinagar", "Shimla"};

string Ahmedabad[]={"Ahmedabad", "Chandkheda", "Sabarmati", "Thaltej", "Ambawadi", "Ambli"};

string Mumbai[]={"Mumbai", "Andheri" ,"Bandra", "Borivali", "Dahisar", "Goregaon"};

string Delhi[]={"Delhi", "Sadar bazar", "Tilak nagar", "Rohini", "Lajpat Nagar", "Kirti Nagar"};

string Bangalore[]={"Bangalore", "Jayanagar", "Malleshwaram", "Murphy Town", "HSR Layout", "Koramangala"};

int graph[V][V]={   {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 3},   //Store Location
					{4, 0, 0, 0, 0, 0, 0, 6, 0, 0, 2},	 //Mumbai
					{0, 0, 0, 0, 9, 4, 0, 0, 0, 0, 11},	 //Delhi
					{0, 0, 0, 0, 1, 0, 0, 0, 16, 5, 0},	 //Bangalore
					{0, 0, 9, 1, 0, 8, 13, 0, 10, 6, 0}, //Jaipur	
					{0, 0, 4, 0, 8, 0, 0, 3, 17, 0, 7},	 //Bhopal
					{0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 7},	 //Goa
					{0, 6, 0, 0, 0, 3, 0, 0, 5, 0, 0},	 //Ahmedabad
					{0, 0, 0, 16, 10, 17, 0, 5, 0, 0, 0},//Kolkata
					{0, 0, 0, 5, 6, 0, 0, 0, 0, 0, 0},	 //Srinagar
					{3, 2, 11, 0, 0, 7, 7, 0, 0, 0, 0}  };//Shimla
					
//----------------------Ahmedabad--------------------------------				
int AhmGraph[V1][V1]={ 	{ 0, 4, 4, 0, 0, 0 },
						{ 4, 0, 2, 0, 0, 0 },   
						{ 4, 2, 0, 3, 2, 4 },	
						{ 0, 0, 3, 0, 0, 3 },	
						{ 0, 0, 2, 0, 0, 3 },
						{ 0, 0, 4, 3, 3, 0 } };	
						
//---------------------Mumbai------------------------------------
int MumGraph[V1][V1]={ 	{ 0, 4, 0, 2, 0, 0 },
						{ 4, 0, 3, 1, 0, 6 },	
						{ 0, 3, 0, 4, 0, 7 },	
						{ 2, 1, 4, 0, 9, 0 },
						{ 0, 0, 0, 9, 0, 5 },	
						{ 0, 6, 7, 0, 5, 0 } };	

//-----------------------Delhi---------------------------------------
int DelGraph[V1][V1]={ 	{ 0, 9, 15, 6, 0, 0 },
						{ 9, 0, 7, 0, 0, 8 },
						{ 15, 7, 0, 8, 9, 5 },
						{ 6, 0, 8, 0, 11, 0 },
						{ 0, 0, 9, 11, 0, 0 },
						{ 0, 8, 5, 0, 0, 0 } };	

//----------------------Bangalore----------------------------------------
int BangGraph[V1][V1]={ 	{ 0, 6, 3, 0, 0, 1 },
						{ 6, 0, 0, 2, 0, 5 },	
						{ 3, 0, 0, 0, 3, 5 },
						{ 0, 2, 0, 0, 6, 4 },	
						{ 0, 0, 3, 6, 0, 6 },	
						{ 1, 5, 5, 4, 6, 0 } };	

//----------------------------------------------------------------------------------

int city(){
	int opt;
	cout << "\nThe delivery is available for following Areas : \n" << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        City       |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Mumbai         |"<<endl;
    cout<<"\n |     2    |    Delhi          |"<<endl;
    cout<<"\n |     3    |    Bangalore      |"<<endl;
	cout<<"\n |     4    |    Jaipur         |"<<endl;
    cout<<"\n |     5    |    Bhopal         |"<<endl;
    cout<<"\n |     6    |    Goa            |"<<endl;
    cout<<"\n |     7    |    Ahmedabad      |"<<endl;
    cout<<"\n |     8    |    Kolkata        |"<<endl;
	cout<<"\n |     9    |    Srinagar       |"<<endl;
    cout<<"\n |    10    |    Shimla         |"<<endl;
    cout<<"---------------------------------\n"<<endl;

    

	cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
}




int mum(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Mumbai: " << endl;
    
    cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA           |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Andheri            |"<<endl;
    cout<<"\n |     2    |    Bandra             |"<<endl;
    cout<<"\n |     3    |    Borivali           |"<<endl;
	cout<<"\n |     4    |    Dahisar            |"<<endl;
    cout<<"\n |     5    |    Goregaon           |"<<endl;
    cout<<"---------------------------------\n"<<endl;
    
    
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
                              
}

int Ahm(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Ahmedabad: " << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA       |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Chandkheda     |"<<endl;
    cout<<"\n |     2    |    Sabarmati      |"<<endl;
    cout<<"\n |     3    |    Thaltej        |"<<endl;
	cout<<"\n |     4    |    Ambawadi       |"<<endl;
    cout<<"\n |     5    |    Ambli          |"<<endl;
    cout<<"---------------------------------\n"<<endl;
    
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
                              
}

int del(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Delhi: " << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA        |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Sadar bazar     |"<<endl;
    cout<<"\n |     2    |    Tilak nagar     |"<<endl;
    cout<<"\n |     3    |    Rohini          |"<<endl;
	cout<<"\n |     4    |    Lajpat Nagar    |"<<endl;
    cout<<"\n |     5    |    Kirti Nagar     |"<<endl;
    cout<<"---------------------------------\n"<<endl;
	
    
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
                              
}

int bang(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Bangalore: " << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA       |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Jayanagar      |"<<endl;
    cout<<"\n |     2    |    Malleshwaram   |" <<endl;
    cout<<"\n |     3    |    Murphy Town    |"<<endl;
	cout<<"\n |     4    |    HSR Layout     |"<<endl;
    cout<<"\n |     5    |    Koramangala    |"<<endl;
    cout<<"---------------------------------\n"<<endl;
    
    cout << "Enter your option :" << endl;
    cin >> opt;
    return opt;
                              
}


int FurthurArea(int option){
	int opt;
	switch(option){
			
			case 1: 
			{
				prims(MumGraph,distanceP);
				opt=mum();
				addressF=Mumbai[opt];
			}
			break;
			
			case 2:
			{
				prims(DelGraph,distanceP);
				opt=del();
				addressF=Delhi[opt];
			}
			break;
			
			case 3:
			{
				prims(BangGraph,distanceP);
				opt=bang();
				addressF=Bangalore[opt];
			}
			break;
			
			case 7:
			{
				prims(AhmGraph,distanceP);
				opt=Ahm();
				addressF=Ahmedabad[opt];
			}
			break;
		}
		
	return opt;
}

//---------------------------------------------------------------------------------------------


int main()
{
	shop =new Shop;
	string shopname;
	cout<<"Enter the Name of Ecommerce Store:"<<endl;
	getline(cin,shopname);
	shop->name=shopname;
	string shopaddress;
	cout<<"Enter the Location of Ecommerce Store:"<<endl;
	getline(cin,shopaddress);
	shop->address=shopaddress;

	shop->product=new string[11]{"","Sony FX30          ", "Sony FR7           ", "Canon EOS 90D      ",
								 "Nikon D6           ", "Panasonic Lumix G10","Canon EOS 250D     ",
								  "Sony Alpha 7       ", "Nikon D750         ", "Panasonic Lumix GH5",
								"Canon EOS 5D Mark "};
								
								
	shop->price=new int[11]{0, 45500, 175000, 289000, 155700, 75000, 210000, 199999, 100000, 45000, 500000};
	int choice = -99;

	
	do
    {

        cout << endl;
        cout << "************************  " << shop->name << "  ************************" << endl;
        cout << "Location : " << shop->address << endl;
        cout << endl;

        cout << endl;
        cout << "************************  Operations  ************************" << endl;
        cout << endl;


        // Order placing
        cout << "1. Display the product and prices" << endl;
		cout << "2. Place order for Take-Away from " <<shop->name<< endl;
        cout << "3. Place order for Home Delivery " << endl;
        cout << "4. Get Order from " <<shop->name<<endl;
        cout << "5. Display all Delivery Orders" << endl;
        cout << "6. Display all Take-Away Orders" << endl;
        cout << "0. EXIT " << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        // for taking input of Customer Details
        string name;
        int quantity;
        int productNumber;
        double bill;
        string address;
        int orderId;
        int distance;
		
        switch (choice)
        {
        
        //--------------------------------CASE 1-----------------------------------------------------
        case 1:
		{
		
		cout<<"\n---------------------------------------------------------------------";
        cout<<"\n | ITEM NO. |             ITEM NAME               | ORIGINAL PRICE  |";
        cout<<"\n---------------------------------------------------------------------";
        cout<<"\n |    1     |  	       	  Sony FX30               |       45500     |"<<endl;
        cout<<"\n |    2     | 	    	  Sony FR7 	              |       175000    |"<<endl;
        cout<<"\n |    3     |            Canon EOS 90D            |       289000    |"<<endl;
        cout<<"\n |    4     |              Nikon D6               |       155700    |"<<endl;
        cout<<"\n |    5     |          Panasonic Lumix G10        |       75000     |"<<endl;
        cout<<"\n |    6     |            Canon EOS 250D           |       210000    |"<<endl;
        cout<<"\n |    7     |            Sony Alpha 7             |       199999    |"<<endl;
        cout<<"\n |    8     |             Nikon D750              |       100000    |"<<endl;
        cout<<"\n |    9     |          Panasonic Lumix GH5        |       45000     |"<<endl;
        cout<<"\n |    10    |           Canon EOS 5D Mark         |       500000    |";
        cout<<"\n---------------------------------------------------------------------"<<endl;
		}
		break ;	
        	
        	
        //-----------------------------------CASE 2--------------------------------------------------
        case 2:                                   
        { 
			cout << "Enter the name of the customer: ";
            cin >> name;
			cout << "Enter the product Number: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;
            cout << "Enter orderID of one or two letters: ";
            cin >> orderId;


            bill = quantity * shop->price[productNumber];
            root=insertion(name, quantity, shop->product[productNumber], bill, orderId, root);
            cout <<"\n------------------------------------"<< endl;
            cout << "**** Your order has been placed *****" << endl;
            cout << "Total amount : " << bill << endl;
			cout << "order ID :" << orderId << endl;
            cout << "You can get your order from " <<shop->name<< endl;
            cout <<"-------------------------------------\n"<< endl;
            
        }
        break;

		//-----------------------------------CASE 3--------------------------------------------------
        case 3:

        {                                               
            dijkstra(graph,dist,0);

            do
            {
                optionDelivery=city();   //Return The index of city that has been selected

            } while (!(optionDelivery >= 0 && optionDelivery <= 10));
            
            
            if(optionDelivery==1 || optionDelivery==2 || optionDelivery==3 || optionDelivery==7  )
			{
            	
            	do
            	{
            		optionDelivery1=FurthurArea(optionDelivery);  //Return index of area in a city
            		
				} while(!(optionDelivery1 >=0 && optionDelivery1 <=5));
				
				address= CityName[optionDelivery] +" " +addressF;
				distance=dist[optionDelivery] + distanceP[optionDelivery1];
				
			}
			else 
			{
				address = CityName[optionDelivery];
				distance=dist[optionDelivery];
				
			}


            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the product Number: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;


            int deliveryChargesPerKM = 20;
            int deliveryCharges = deliveryChargesPerKM * distance;
            bill = quantity * shop->price[productNumber] + deliveryCharges;

            placeOrderHomeDeliveryCustomer(name, shop->product[productNumber], quantity, bill, address, deliveryCharges, distance );
        }
        break;
        
        //-----------------------------------CASE 2--------------------------------------------------
        case 4 :
        {
        	// Get Order from Warehouse

            cout << "Enter the Order Id: ";
            cin >> orderId;
			
			takeAway *cust=search(root,orderId);
			
			if (cust == NULL){
			
				cout << "\n----------------------------------"<< endl;
                cout << "No such order is in the "<<shop->name<< endl;
                cout << "-----------------------------------\n"<< endl;
            }else
			{
				
                root=deleteNode(root,orderId);
                cout << "\n----------------------------------"<< endl;
				cout << "Your order is ready for collection" << endl;
				cout << "  Please get it from the counter" << endl;
				cout << "-----------------------------------\n"<< endl;
			}
		}
		break;
		
		//-----------------------------------CASE 5--------------------------------------------------
		case 5 :
		{
			
            displayAllOrdersHomeDeliveryCustomers();
		}
        break;
        
        //-----------------------------------CASE 6--------------------------------------------------
        case 6 :
    	{
    	
    		displayTakeAway(root);
			
		}
        break ;
        
    	}
    

    } while (choice != 0);

    cout << "Thank you for Using our Services " << endl;
	
	return 0;
}
