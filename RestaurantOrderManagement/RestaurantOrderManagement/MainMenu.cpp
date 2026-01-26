#pragma once
#include "MainMenu.h"

//title setw(50)


//all function about password
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


std::string inputPassword()
{
	std::string password;
	char ch;

	while (true)
	{
		ch = readChar();

		if (ch == '\n' || ch == '\r' || ch == 13) // Enter
			break;

		else if (ch == 8 || ch == 127) // Backspace
		{
			if (!password.empty())
			{
				password.pop_back();
				std::cout << "\b \b" << std::flush;
			}
		}
		else
		{
			password += ch;
			std::cout << "*" << std::flush;
		}
	}

	std::cout << std::endl;
	return password;
}

//delete buffer for string
void cinIgnore()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


//all checking function
bool hasDigit(const std::string& s)
{
	for (unsigned char c : s)
	{
		if (std::isdigit(c))
			return true;
	}
	return false;
}

bool hasLetter(const std::string& s)
{
	for (unsigned char c : s)
	{
		if (std::isalpha(c))
			return true;
	}
	return false;
}

bool hasSpecialChar(const std::string& s)
{
	for (unsigned char c : s)
	{
		if (!std::isalnum(c))
			return true;
	}
	return false;
}




//all print function
void printLine(char c, const int width)
{
	std::cout << std::string(width, c) << std::endl; // use string to set default line
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

void printMenuManagement(std::vector<MenuItem> menu_list)
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
		std::cout << std::left
			<< std::setw(6) << menu_list[i].getItemId()
			<< std::setw(35) << menu_list[i].getItemName()
			<< std::setw(15) << menu_list[i].getPrice()
			<< std::setw(15) << menu_list[i].getCategory()
			<< std::setw(10) << (menu_list[i].isAvailable() ? "Yes" : "No")
			<< std::endl;
	}
}




//all modify method


//order modify screen which will be called in showOrderWaiter
void orderModifyWaiter(Order& order,Staff staff)
{
	bool modify_order = true;
	do
	{
		std::vector<OrderItem> order_item_list = order.getOrderItems(); // get all orderitem in this order
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
				if (order_item_list.empty())
				{
					std::cout << "No orderitem in order, please add orderitem, can't send to kitchen" << std::endl;
					continue;
				}
				char confirm;
				std::cout << "Confirm send to kitchen ? y/n"; std::cin >> confirm;
				if (confirm == 'y') order.sendToKitchen(staff.getId());
				else continue;
			}


			else if (choice == 'C' || choice == 'c')
			{
				char confirm;
				std::cout << "Are you sure customer has done their food ? y/n"; std::cin >> confirm;
				if (confirm == 'y') order.markCompleted(staff.getId());
				else continue;
			}

			//loop to updating order
			else if (choice == 'U' || choice == 'u')
			{
				bool updating_order = true;
				do
				{
					std::cout << "[A] Add Order Item\t"
						<< "[R] Remove Order Item\t"
						<< "[U] Update note\n"
						<< "[Q] Quantity modify\t"
						<< "[B] Back\n";
					char order_item_choice;
					std::cout << "Your choice:"; std::cin >> order_item_choice;
					if (order_item_choice == 'A' || order_item_choice == 'a')
					{
						std::optional<MenuItem> menu_item;
						bool retry = false;

						do
						{
							retry = false;
							try
							{
								std::string menu_item_id;
								std::cout << "Enter item id (e.g M0001): ";
								std::cin >> menu_item_id;

								menu_item = MenuItem::getMenuItemById(menu_item_id);

								if (!menu_item->isAvailable())
								{
									std::cout << "Item is not available\n";
									retry = true;
								}
							}
							catch (const std::runtime_error& e)
							{
								std::cout << e.what() << std::endl;
								retry = true;
							}
						} while (retry == true);
						int quantity;
						std::cout << "Enter Quantity: "; std::cin >> quantity;
						try
						{
							order.addOrderItem(*menu_item, quantity);
							std::cout << "Success! Added" << quantity << "x" << menu_item->getItemName() << std::endl;
						}
						catch (std::runtime_error& e)
						{
							std::cout << e.what() << std::endl;
						}

					}

					else if (order_item_choice == 'R' || order_item_choice == 'r')
					{
						std::string order_item_id;
						std::cout << "Enter order_item_id order from up to down (first order is OM001, second OM002,...): "; std::cin >> order_item_id;
						try
						{
							char confirm;
							std::cout << "You sure you want to remove this order item ? y/n"; std::cin >> confirm;
							if (confirm == 'y')
							{
								order.removeOrderItem(order_item_id);
							}
							else continue;
						}
						catch (std::runtime_error& e)
						{
							std::cout << e.what() << std::endl;
						}

					}


					else if (order_item_choice == 'U' || order_item_choice == 'u')
					{
						std::string new_note;
						std::cout << "Enter Note:"; 
						cinIgnore();						
						std::getline(std::cin, new_note);
						order.setNote(new_note);
					}

					else if (order_item_choice == 'Q' || order_item_choice == 'q')
					{
						std::string order_item_id; int new_quantity;
						std::cout << "Enter order_item_id order from up to down (First is OM001, second OM002,...): "; std::cin >> order_item_id;
						do
						{
							std::cout << "Enter new quantity:"; std::cin >> new_quantity;
							if (new_quantity <= 0 || new_quantity >= 40) std::cout << "Invalid quantity or quantity too high, try again" << std::endl;
						} while (new_quantity <= 0 || new_quantity >= 40);
						std::cin.ignore();
						try
						{
							char confirm;
							std::cout << "You sure you want to update this order item ? y/n"; std::cin >> confirm;
							if (confirm == 'y')
							{
								order.updateOrderItemQuantity(order_item_id, new_quantity);
							}
							else continue;
						}
						catch (std::runtime_error& e)
						{
							std::cout << e.what() << std::endl;
						}

					}

					else if (order_item_choice == 'B' || order_item_choice == 'b')
					{
						updating_order = false;
					}

					else
					{
						std::cout << "Wrong input, please try again" << std::endl;
						continue;
					}

				} while (updating_order == true);
			}

			else if (choice == 'B' || choice == 'b')
			{
				modify_order = false;
			}
		}

	} while (modify_order == true);
}



void orderModifyKitchenStaff(Order& order, Staff staff) //called by showOrderKitchenStaff
{
	bool modify_order = true;
	do
	{
		std::vector<OrderItem> order_item_list = order.getOrderItems(); // get all orderitem in this order
		printOrder(order, staff, order_item_list);
		std::cout << "[V] View Menu\t"
			<< "[A] Set Preparing\t"
			<< "[S] Set Ready\t"
			<< "[B] Back\n";
		char choice;
		std::cout << "choice: "; std::cin >> choice;

			if (choice == 'V' || choice == 'v')
			{
				showMenuScreen();
			}

			else if (choice == 'A' || choice == 'a')
			{
				char confirm;
				std::cout << "Confirm set to preapring ? y/n"; std::cin >> confirm;
				try
				{
					if (confirm == 'y') order.markPreparing(staff.getId());

					else continue;
				}
				catch (std::runtime_error& e)
				{
					std::cout << e.what() << std::endl;
				}
			}

			else if (choice == 'S' || choice == 's')
			{
				char confirm;
				try
				{
					std::cout << "Are you sure this order is ready ? y/n"; std::cin >> confirm;
					if (confirm == 'y') order.markReady(staff.getId());
					else continue;
				}
				catch (std::runtime_error& e)
				{
					std::cout << e.what() << std::endl;
				}
			}

			else if (choice == 'B' || choice == 'b')
			{
				modify_order = false;
			}

	} while (modify_order == true);
}



void orderModifyCashier(Order& order, Staff staff, Cashier cashier)
{
	bool modify_order = true;
	do
	{
		std::vector<OrderItem> order_item_list = order.getOrderItems(); // get all orderitem in this order
		printOrder(order, staff, order_item_list);
		std::cout << "[V] View Menu\t"
			<< "[P] Process Payment\t"
			<< "[B] Back\n";
		char choice;
		std::cout << "Your choice: "; std::cin >> choice;
		if (choice == 'V' || choice == 'v')
		{
			showMenuScreen();

		}

		else if (choice == 'P' || choice == 'p')
		{
			char confirm;; float total_amount;
			float total = order.getTotalAmount();
			bool retry = false;

			do //check if customer give enough money
			{
				retry = false;
				std::cout << "Amount received: "; std::cin >> total_amount;
				if (total_amount < total)
				{
					std::cout << "Not enough money, please input again";
					std::cin >> total_amount;
					retry = true;
				}
			} while (retry == true);

			std::cout << "change: " << (total_amount - total); //how much money cashier will return to customer
			std::cout << "Confirm ? y/n"; std::cin >> confirm;
			if (confirm == 'y' || confirm == 'Y')
			{
				Invoice invoice = Invoice::generate(order,cashier); //generate invoice of this order
				cashier.ProcessPayment(order, invoice);
			}
			else
			{
				std::cout << "Payment has been cancelled" << std::endl;
				continue;
			}
		}

		else if (choice == 'B' || choice == 'b')
		{
			modify_order = false;
		}

		else
		{
			std::cout << "wrong input, please input what is showed on the screen" << std::endl;
			continue;
		}

	} while (modify_order == true);

}


void staffModify(std::vector<Staff>& staff_list, Manager manager)
{
	bool modify_staff = true;
	do
	{
		clearScreen();
		printStaffList(staff_list);
		std::cout << "[A] Add Staff\t"
			<< "[U] Update Staff\t"
			<< "[R] Remove Staff\n"
			<< "[B] Back to Menu Management\n";
		char choice;
		std::cout << "Choice: "; std::cin >> choice;


		if (choice == 'A' || choice == 'a')
		{
			try
			{
				std::string staff_id;
				std::string staff_name;
				std::string password; std::string hash_password;
				std::string phone;
				std::string role;

				std::cout << "Enter staff id: "; std::cin >> staff_id;
				std::cout << "Enter staff name: "; std::cin.ignore(); std::getline(std::cin, staff_name);
				std::cout << "Enter staff password: "; std::cin >> password; hash_password = hashPassword(password);

				bool retry;
				do
				{
					retry = false;
					std::cout << "Enter staff phone: "; std::cin >> phone;
					if (phone.size() != 10 || hasSpecialChar(phone) == true || hasLetter(phone) == true)
					{
						std::cout << "Invalid phone number, phone length is 10 or contain special character\n";
						retry = true;
					}
				} while (retry == true);

				std::cout << "Enter staff role: "; std::cin >> role;
				

				Staff staff(staff_id, staff_name, hash_password, phone, role);
				
				char confirm;
				std::cout << "Are you sure you want to add this staff ? y/n"; std::cin >> confirm;
				if (confirm == 'y' || confirm == 'Y')
				{
					manager.addStaff(staff);

					std::cout << "Staff has been added successfully";
				}
				else continue;

			}
			catch (std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}

		}

		else if (choice == 'U' || choice == 'u')
		{
			try
			{
				std::string staff_id;
				std::string staff_name;
				std::string password; std::string hash_password;
				std::string phone;
				std::string role;

				std::cout << "Enter staff id: "; std::cin >> staff_id;
				std::cout << "Enter staff name: "; std::cin.ignore(); std::getline(std::cin, staff_name);
				std::cout << "Enter staff password: "; std::cin >> password; hash_password = hashPassword(password);

				bool retry;
				do
				{
					retry = false;
					std::cout << "Enter staff phone: "; std::cin >> phone;
					if (phone.size() != 10 || hasSpecialChar(phone) == true || hasLetter(phone) == true)
					{
						std::cout << "Invalid phone number, phone length is 10 or contain special character\n";
						retry = true;
					}
				} while (retry == true);

				std::cout << "Enter staff role: "; std::cin >> role;


				Staff staff(staff_id, staff_name, hash_password, phone, role);

				char confirm;
				std::cout << "Are you sure you want to update this staff ? y/n"; std::cin >> confirm;
				if (confirm == 'y' || confirm == 'Y')
				{
					manager.updateStaff(staff_id,staff);
					std::cout << "Staff has been updated successfully";
				}
				else continue;
			}
			catch (std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}

		}

		else if (choice == 'R' || choice == 'r')
		{
			try
			{
				std::string id;
				std::cout << "Enter staff id: "; std::cin >> id;
				char confirm;
				std::cout << "Are you sure you want to delete this staff ? y/n"; std::cin >> confirm;
				if (confirm == 'y')
				{
					manager.removeStaff(id);
					std::cout << "Staff has been removed successfully" << std::endl;
				}
				else continue;
			}
			catch (std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}

		}

		else if (choice == 'B' || choice == 'b')
		{
			modify_staff = false;
		}
		else
		{
			std::cout << "wrong input, please input exacly what is showed on the screen" << std::endl;
			continue;
		}


	} while (modify_staff == true);
}



void saleModify(Manager manager)
{
	bool modify_sale;
	do
	{
		printLine('=');
		std::cout << std::setw(50) << "SALES REPORT SETUP" << std::endl;
		printLine('=');
		std::cout << "[1] Date Range\n"
			<< "[0] Back\n";
		printLine('-');
		char choice;
		std::cout << "choice: "; std::cin >> choice;

		if (choice == '1')
		{
			try
			{
				std::string start_date; std::string end_date;
				std::cout << "Date start (YYYY-MM-DD): "; std::cin >> start_date;
				std::cout << "Date end(YYYY-MM-DD): "; std::cin >> end_date;
				manager.viewSalesReport(DateTimeUtils::stringToTimePoint(start_date), DateTimeUtils::stringToTimePoint(end_date));
			}
			catch (std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}

		}
		
		else if (choice == '0')
		{
			modify_sale = false;
		}

		else
		{
			std::cout << "Wrong input, please input as what is showing on the screen" << std::endl;
			continue;
		}


	} while (modify_sale == true);


}



//all screen method

//showmenuscreen function
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
		clearScreen();
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
	bool waiter_screen = true; char waiter_choice;
	do
	{
		std::vector<Order> order_list = waiter.viewActiveOrder(); //get order list that only waiter see
		printOrderMenu(order_list);
		std::cout << "[N] New Order\t"
			<< "[V] View Detail(Input ID)\t"
			<< "[0] logout\n";
		std::cout << "Choice: "; std::cin >> waiter_choice;
		clearScreen();

		if (waiter_choice == 'N') //waiter input order detail
		{
			clearScreen();
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
			try
			{
				Order order = waiter.createOrder(table_number, customer_name, note);
				orderModifyWaiter(order, staff);
			}
			catch (std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}
			
		}


		else if (waiter_choice == 'V')
		{
			clearScreen();
			int id;
			std::cout << "Enter order_id: "; std::cin >> id;
			try
			{
				Order modify_order = Order::getOrderById(id);

				bool found = false;
				for (auto& o : order_list) //check if user input the right order id which is showed on the screen
				{
					if (o.getOrderId() == id)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					std::cout << "You don't have permission to view this order\n";
					continue;
				}

				orderModifyWaiter(modify_order, staff);
			}
			catch (const std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}

		}

		else if (waiter_choice == '0')
		{
			waiter_screen = false;
		}
		else
		{
			std::cout << "Wrong input, please input what is showed on the screen, try again"<<std::endl;
		}

	} while (waiter_screen == true);
}



//show screen of kitchenstaff
void showOrderKitchenStaff(Staff staff, KitchenStaff kitchen_staff)
{
	bool kitchen_screen = true;
	do
	{
		std::vector<Order> order_list = kitchen_staff.viewPendingOrders(); //get list that only chef see
		printOrderMenu(order_list);
		std::cout << "[V] View Detail(Input ID)\t" << "[0] logout\n";
		char choice;
		std::cout << "Choice: "; std::cin >> choice;
		clearScreen();
		if (choice == 'V' || choice == 'v')
		{
			try
			{
				int id;
				std::cout << "Enter order id: "; std::cin >> id;
				Order order = Order::getOrderById(id);

				bool found = false;
				for (auto& o : order_list) //check if user input the right order id which is showed on the screen
				{
					if (o.getOrderId() == id)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					std::cout << "You don't have permission to view this order\n";
					continue;
				}

				orderModifyKitchenStaff(order, staff);
			}
			catch(std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		else if (choice == '0')
		{
			kitchen_screen = false;
		}
		else
		{
			std::cout << "Wrong input, please input what is showed on the screen, try again" << std::endl;
		}

	} while (kitchen_screen == true);
}




//Cashier screen
void showOrderCashier(Staff staff, Cashier cashier)
{
	bool cashier_screen = true;
	do
	{
		std::vector<Order> order_list = cashier.viewCompletedOrders(); //get order list that only cashier can see
		printOrderMenu(order_list);
		std::cout << "[V] View Detail(Input ID)\t" << "[0] logout\n";
		char choice;
		std::cout << "Choice: "; std::cin >> choice;
		clearScreen();
		if (choice == 'V' || choice == 'v')
		{
			try
			{
				int id;
				std::cout << "Enter Order ID: "; std::cin >> id;
				Order order = Order::getOrderById(id);

				bool found = false;
				for (auto& o : order_list) //check if user input the right order id which is showed on the screen
				{
					if (o.getOrderId() == id)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					std::cout << "You don't have permission to view this order\n";
					continue;
				}

				orderModifyCashier(order, staff, cashier);

			}
			catch (std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}
		}


		else if (choice == '0')
		{
			cashier_screen = false;
		}


		else
		{
			std::cout << "wrong input, please enter exacly what is on the screen" << std::endl;
			continue;
		}


	} while (cashier_screen == true);
}




//Menu mangement of Manager
void showMenuMangement(Staff staff, Manager manager)
{
	bool manager_screen = true;
	do
	{
		std::vector<MenuItem> menu_list = MenuItem::getAllMenuItems();
		printMenu(menu_list);
		std::cout << "[A] Add New Dish\t"
			<< "[E] Edit dish\t"
			<< "[R] Remove Dish\n"
			<< "[S] Staff Management\t"
			<< "[V] View Sale Report\t"
			<< "[0] logout\n";
		char choice;
		std::cout << "Your choice:"; std::cin >> choice;


		if (choice == 'A')
		{
			std::cout << "---ADD NEW DISH---"<<std::endl;
			std::string menu_id, menu_name, menu_category;
			float price; bool is_available;
			std::cout << "Enter ID  (e,g M0001):"; std::cin >> menu_id;
			cinIgnore(); //delete buffer

			std::cout << "Enter Name: "; std::getline(std::cin, menu_name);
			std::cout << "Enter Category: "; std::getline(std::cin, menu_category);

			//validate user input
			bool retry = true;
			do
			{
				retry = false;
				std::cout << "Enter price: "; std::cin >> price;
				if (price <= 0)
				{
					std::cout << "Invalid price, please enter again";
					retry = true;
				}
			} while (retry == true);

			//validate user input
			int available;
			while (true)
			{
				std::cout << "Is available ? (1:Yes, 0:No): ";
				std::cin >> available;

				// check input if user enter char
				if (std::cin.fail())
				{
					std::cin.clear(); // clear error flag
					cinIgnore();
					std::cout << "Invalid input. Please enter 1 or 0.\n";
					continue;
				}

				// check logical value
				if (available == 0 || available == 1)
					break;

				std::cout << "Only 1 (Yes) or 0 (No) is allowed.\n";
			}
			is_available = (available == 1);


			MenuItem item(menu_id, menu_name, price, menu_category, is_available);
			manager.addMenuItem(item);

			//called when a menuitem is added but there is no ingredient for it
			if (!InventoryItemMenu::hasRequirement(item.getItemId()))
			{
				char choice;
				std::cout << "[System]: WARNING: No inventory requirement found. Create now? (y/n): ";
				std::cin >> choice;

				if (choice == 'y' || choice == 'Y')
				{
					int serving;
					std::cout << "Enter Serving Size: ";
					std::cin >> serving;

					while (true)
					{
						std::string inv_id;
						float qty; std::string unit;

						std::cout << "Ingredient ID & Amount (I01 0.2) or 0 to confirm: ";
						std::cin >> inv_id;
						
						//check if ingredient exist
						if (!InventoryItem::exists(inv_id))
						{
							std::cout << "This ingredient don't exist in inventory, please try again" << std::endl;
							continue;
						}

						if (inv_id == "0") break;

						std::cin >> qty;
						std::cout << "unit: "; std::cin >> unit;
						try
						{
							InventoryItemMenu::createRequirement(item.getItemId(), inv_id, qty, unit, serving);
						}
						catch (std::runtime_error& e)
						{
							std::cout << e.what() << std::endl;
						}
					}

					std::cout << "[System]: Requirement created!\n";
				}
			}


		}


		else if (choice == 'E')
		{
			std::string id;
			std::cout << "Enter Menu ID: "; std::cin >> id;
			try
			{
				std::string id, new_name; float new_price;
				std::cout << "Enter existed menu item id: "; std::cin >> id;
				std::cout << "Enter new menu item name: "; std::cin >> new_name;
				std::cout << "Enter new price: "; std::cin >> new_price;
				
				char confirm;
				std::cout << "Are you sure you want to update ? y/n "; std::cin >> confirm;
				if (confirm == 'y')
				{
					manager.updateMenuItem(id, new_name, new_price);
					std::cout << "Menu item " + id + " has been updated successfuly" << std::endl;
				}
				else continue;

			}
			catch (std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
			}

		}


		else if (choice == 'R')
		{
			std::string id;
			std::cout << "Enter menu item ID: "; std::cin >> id;
			char confirm;
			std::cout << "Are you sure you want to delete this item ?";
			std::cin >> confirm;

			if (confirm == 'y')
			{
				try
				{
					manager.removeMenuItem(id);
					std::cout << "Menu Item " + id + " has been removed successfully" << std::endl;
				}
				catch (std::runtime_error& e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else continue;
		}

		else if (choice == 'S' || choice == 's')
		{
			//call staff modify
			std::vector<Staff> staff_list = Staff::getAllStaff();
			staffModify(staff_list,manager);

		}

		else if (choice == 'V' || choice == 'v')
		{
			//call sale report modify
			saleModify(manager);
		}



		else if (choice == '0')
		{
			manager_screen = false;
		}

		else
		{
			std::cout << "wrong input, please input what is showing on the screen" << std::endl;
		}
	} while (manager_screen == true);
}