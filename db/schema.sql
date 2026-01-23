DROP DATABASE IF EXISTS RestaurantOrderManagement;
create database RestaurantOrderManagement;
use RestaurantOrderManagement;
create table Staff
(
	staff_id char(5) primary key not null,
    staff_name varchar(30) not null,
    password varchar(40) not null,
    phone char(10) not null,
    role varchar(30) not null
);

create table Customer
(
	customer_id int auto_increment primary key not null,
    customer_name varchar(50) not null,
    phone char(10)
);

create table MenuItem
(
	item_id char(5) primary key not null ,
    item_name varchar(30) not null,
    price float not null,
    category varchar(30) not null,
    is_availabe boolean not null
);

create table InventoryItem
(
	inventory_id char(5) primary key not null,
    item_name varchar(30) not null,
    quantity float not null,
    unit varchar(30) not null
);

create table InventoryItemMenu
(
	item_id char(5) not null,
    serving_size int not null,
    quantity_required float not null,
    unit varchar(30) not null,
    inventory_id char(5) not null,
    primary key(item_id, inventory_id),
    FOREIGN KEY(item_id) REFERENCES MenuItem(item_id),
    FOREIGN KEY(inventory_id) REFERENCES InventoryItem(inventory_id)
);

create table OrderTable
(
	order_id int auto_increment not null primary key,
    table_number int not null,
    order_time datetime default current_timestamp,
    total_amount float not null,
    note varchar(50) not null,
    order_status ENUM('CREATED','PENDING','PREPARING','READY','COMPLETED','CANCELLED') not null default 'CREATED',
    customer_name varchar(50) not null,
    staff_id char(5) not null,
    customer_id int,
    FOREIGN KEY(staff_id) REFERENCES Staff(staff_id),
    FOREIGN KEY(customer_id) REFERENCES Customer(customer_id)
);


create table OrderItem
(
	order_item_id char(5) not null,
    order_item_name varchar(50) not null,
    quantity int not null,
    price float,
    order_id int not null,
    item_id char(5) not null,
    primary key(order_id, order_item_id),
    FOREIGN KEY(order_id) REFERENCES OrderTable(order_id),
    FOREIGN KEY(item_id) REFERENCES MenuItem(item_id)
);

create table Invoice
(
	invoice_id int auto_increment not null primary key,
    issue_date datetime default current_timestamp,
    total_price float,
    invoice_status ENUM('PENDING', 'PAID', 'REFUNDED') not null default 'PENDING',
    order_id int not null,
    staff_id char(5) not null,
    FOREIGN KEY(order_id) REFERENCES OrderTable(order_id),
    FOREIGN KEY(staff_id) REFERENCES Staff(staff_id)
);

create table StaffOrder
(
	staff_id char(5) not null,
    order_time datetime default current_timestamp,
    order_status ENUM('CREATED','PENDING','PREPARING','READY','COMPLETED','CANCELLED'),
    order_id int not null,
    PRIMARY KEY(order_id, staff_id),
    FOREIGN KEY(order_id) REFERENCES OrderTable(order_id),
    FOREIGN KEY(staff_id) REFERENCES Staff(staff_id)
);

