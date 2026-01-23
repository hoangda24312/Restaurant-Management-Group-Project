#include "MainMenu.h"

//title setw(50)


void printLine(char c, const int width)
{
	std::cout << std::string(width, c) << std::endl; // use string to set default line
}


std::string hashPassword(const std::string& password) 
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256(
		reinterpret_cast<const unsigned char*>(password.c_str()),
		password.size(),
		hash
	);

	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0')
			<< (int)hash[i];
	}
	return ss.str();
}


void printMenu(const std::vector<MenuItem>& menu_list, bool filter, std::string category)
{
	printLine('-');
	std::cout << std::setw(50) << "MENU" << std::endl;
	printLine('-');
	std::cout << std::left
		<< std::setw(6) << "ID"
		<< std::setw(35) << "Item Name"
		<< std::setw(15) << "Price(VND)"
		<< std::setw(15) << "Category"
		<< std::setw(10) << "Available"
		<< std::endl;
	printLine('-');
	for (int i = 0; i < menu_list.size(); i++)
	{
		if (filter == true &&
			menu_list[i].getCategory() != category) continue;
		std::cout << std::left
			<< std::setw(6) << menu_list[i].getItemId()
			<< std::setw(35) << menu_list[i].getItemName()
			<< std::setw(15) << menu_list[i].getPrice()
			<< std::setw(15) << menu_list[i].getCategory()
			<< std::setw(10) << (menu_list[i].isAvailable() ? "Yes": "No")
			<< std::endl;
	}
}

void loginScreen()
{
	printLine('=');
	std::cout << std::setw(50)<<"SON TUNG ATM RESTAURANT" << std::endl;
	printLine('=');
	std::cout << "1.Customer" << std::endl;
	std::cout << "2.Staff" << std::endl;
	std::cout << "3.Exit" << std::endl;
	printLine('-');
}

void printOrderMenu(const std::vector<Order>& order_list)
{
	printLine('=');
	std::cout << std::setw(50) << "CURRENT ORDERS LIST" << std::endl;
	printLine('=');
	std::cout << std::left
		<< std::setw(10) << "Order ID"
		<< std::setw(15) << "Table Number"
		<< std::setw(12) << "Status"
		<< std::setw(20) << "Note"
		<< std::endl;
	printLine('-');
	for (int i = 0; i < order_list.size(); i++)
	{
		std::cout << std::left
			<< std::setw(10) << order_list[i].getOrderId()
			<< std::setw(15) << order_list[i].getTableNumber()
			<< std::setw(12) << enumToString(order_list[i].getStatus())
			<< std::setw(20) << order_list[i].getNote()
			<< std::endl;
	}
}

//print all order_item in a order
void printOrderItemList(std::vector<OrderItem> order_item_list)
{
	for (int i = 0; i < order_item_list.size(); i++)
	{
		std::cout << std::left
			<< std::setw(35) << order_item_list[i].getOrderItemName()
			<< std::setw(15) << order_item_list[i].getQuantity()
			<< std::setw(12) << order_item_list[i].getPrice()
			<< std::setw(20) << order_item_list[i].calculateCost()
			<< std::endl;
	}
}

//print when waiter or chef or cashier view order 
void printOrder(Order order, Staff staff, std::vector<OrderItem> order_item_list)
{
	printLine('=');
	std::cout << std::setw(50) << "ORDER DETAIL - ID: #"<<order.getOrderId() << std::endl;
	printLine('=');

	std::cout << std::left
		<< "Table:" << std::setw(5) << order.getTableNumber()
		<< "Time:" << std::setw(18) << order.getOrderTimeFormatted()
		<< "Staff:" << staff.getName()
		<< std::endl;
	std::cout << "Status:" << enumToString(order.getStatus()) << std::endl;
	printLine('-');

	std::cout << std::left
		<< std::setw(35) << "Item name"
		<< std::setw(15) << "Quantity"
		<< std::setw(12) << "Price(VND)"
		<< std::setw(20) << "Subtotal"
		<< std::endl;

	printLine('-');
	printOrderItemList(order_item_list);
	printLine('-');

	std::cout << std::left << "TOTAL AMOUNT:" << std::right << order.getTotalAmount()<<std::endl;
	printLine('-');
}

//print all staff currently in restaurant
void printStaffList(std::vector<Staff> staff_list)
{
	printLine('=');
	std::cout << std::setw(50) << "STAFF MANAGEMENT" << std::endl;
	printLine('=');

	std::cout << std::left
		<< std::setw(6) << "ID"
		<< std::setw(35) << "Name"
		<< std::setw(12) << "Phone"
		<< std::setw(20) << "Role"
		<< std::endl;

	printLine('-');
	for (int i = 0; i < staff_list.size(); i++)
	{
		std::cout << std::left
			<< std::setw(6) << staff_list[i].getId()
			<< std::setw(35) << staff_list[i].getName()
			<< std::setw(12) << staff_list[i].getPhone()
			<< std::setw(20) << staff_list[i].getRole()
			<< std::endl;
	}
	printLine('-');
}

//all screen method
void showMenuScreen()
{
	auto menu_list = MenuItem::getAllMenuItems();
	bool menu_screen = true;
	printMenu(menu_list);
	do
	{
		std::cout << "[0] Logout\t"
			<< "[1] view only main dish\t"
			<< "[2] view only drink\n"
			<< "[3] view only side dish\t"
			<< "[4] view all dish\n";
		int choice;
		std::cout << "Your choice: ";
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		case 0:
			menu_screen = false;
			break;
		case 1:
			printMenu(menu_list, true, "Main dish");
			break;
		case 2:
			printMenu(menu_list, true, "Drink");
			break;
		case 3:
			printMenu(menu_list, true, "Side dish");
			break;
		case 4:
			printMenu(menu_list);
			break;
		default:
			std::cout << "Incorrect choice, please choose only 1-4";
			break;
		}

	} while (menu_screen == true);
}



//order screen of waiter
void showOrderWaiter(Staff staff,Waiter waiter)
{
	std::vector<Order> order_list = waiter.viewActiveOrder(); //get order list that only waiter see
	bool waiter_screen = true; char waiter_choice;
	do
	{
		printOrderMenu(order_list);
		std::cout << "[N] New Order\t"
			<< "[V] View Detail(Input ID)\t"
			<< "[0] logout\n";
		std::cout << "Choice: "; std::cin >> waiter_choice;

		if (waiter_choice == 'N') //waiter input order detail
		{
			int table_number; std::string customer_name; std::string note;
			std::cout << "--CREATE NEW ORDER--" << std::endl;
			do
			{
				//input order detail
				std::cout << "Enter table number: ";
				std::cin >> table_number;
				if (Order::isTableOccupied(table_number)) std::cout<<"Table number already in use, please choose another\n";
			} while (Order::isTableOccupied(table_number) == true);

			std::cin.ignore(); //because of string
			std::cout << "Enter customer name: "; std::getline(std::cin, customer_name);
			std::cout << "note(optional) "; std::getline(std::cin, note);

			//when create order, waiter will view that order to modify
			Order order = Order::create(table_number, note, customer_name);
			bool modify_order = true; //use to stop loop
			do
			{
				std::vector<OrderItem> order_item_list = order.getOrderItems();
				printOrder(order, staff, order_item_list);
				std::cout << "[V] View Menu\t"
					<< "[S] Send to Kitchen\t"
					<< "[C] Completed\n"
					<< "[U] Update Order\t"
					<< "[B] Back\n";
				char choice;
				std::cout << "choice: "; std::cin >> choice;

				{
					if (choice == 'V' || choice == 'v')
					{
						showMenuScreen();
					}
					else if (choice == 'S' || choice == 's')
					{
						char confirm;
						std::cout << "Confirm send to kitchen ? y/n"; std::cin >> confirm;
						if (confirm == 'y') order.sendToKitchen();
						else continue;
					}
				}

			} while (modify_order == true);
		}


		else if (waiter_choice == 'V')
		{

		}

		else if (waiter_choice == '0')
		{
			waiter_screen = false;
		}

	} while (waiter_screen == true);
}