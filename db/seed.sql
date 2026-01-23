SET FOREIGN_KEY_CHECKS = 1;

INSERT INTO Staff (staff_id, staff_name, password, phone, role) VALUES
('S0001', 'Nguyen Van A', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0901111111', 'Manager'),
('S0002', 'Tran Thi B',   '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0902222222', 'Waiter'),
('S0003', 'Le Van C',     '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0903333333', 'KitchenStaff'),
('S0004', 'Pham Gia D',   '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0904444444', 'Cashier'),
('S0005', 'Hoang Minh E', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0905555555', 'Cashier'),
('S0006', 'Vu Thi F',     '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0906666666', 'Waiterr'),
('S0007', 'Do Van G',     '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0907777777', 'KitchenStaff'),
('S0008', 'Bui Minh H',   '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '0908888888', 'Waiter');

INSERT INTO Customer(customer_name, phone) VALUES
('Son Tung','0910000001'),
('Jack','0910000002'),
('My Tam','0910000003'),
('Den Vau','0910000004'),
('Min','0910000005');


INSERT INTO MenuItem VALUES
('M0001','Beefsteak',250000,'Main dish',1),
('M0002','Pasta',120000,'Main dish',1),
('M0003','Salmon',300000,'Side dish',0),
('M0004','Red Wine',150000,'Drink',1),
('M0005','Caesar Salad',85000,'Appetizer',1);

INSERT INTO InventoryItem VALUES
('ING01','Beef',50,'kg'),
('ING02','Pasta Noodle',30,'kg'),
('ING03','Salmon Fish',20,'kg'),
('ING04','Wine Bottle',100,'bottle'),
('ING05','Vegetable',40,'kg'),
('ING06','Cheese',15,'kg');
INSERT INTO InventoryItemMenu VALUES
('M0001',1,0.3,'kg','ING01'),
('M0001',1,0.1,'kg','ING05'),

('M0002',1,0.2,'kg','ING02'),
('M0002',1,0.05,'kg','ING06'),

('M0003',1,0.25,'kg','ING03'),

('M0004',1,1,'bottle','ING04'),

('M0005',1,0.15,'kg','ING05'),
('M0005',1,0.05,'kg','ING06');
INSERT INTO OrderTable
(table_number,total_amount,note,order_status,customer_name,staff_id,customer_id)
VALUES
(1,500000,'','CREATED','Son Tung','S0002',1),
(2,770000,'','PENDING','Jack','S0002',2),
(3,250000,'','PREPARING','My Tam','S0003',3),
(4,150000,'','READY','Den Vau','S0003',4),
(5,85000,'','COMPLETED','Min','S0002',5),

(6,620000,'No salt','CREATED','Jack','S0002',2),
(7,300000,'','PENDING','Son Tung','S0003',1),
(8,450000,'','PREPARING','My Tam','S0003',3),
(9,120000,'','READY','Den Vau','S0002',4),
(10,770000,'','COMPLETED','Min','S0002',5),

(11,250000,'','CANCELLED','Jack','S0002',2),
(12,500000,'','CREATED','Son Tung','S0003',1),
(13,620000,'','PENDING','My Tam','S0002',3),
(14,150000,'','READY','Den Vau','S0003',4),
(15,85000,'','COMPLETED','Min','S0002',5);
INSERT INTO OrderItem VALUES
('OM001','Beefsteak',2,250000,1,'M0001'),
('OM002','Pasta',1,120000,2,'M0002'),
('OM003','Red Wine',1,150000,2,'M0004'),
('OM004','Beefsteak',1,250000,3,'M0001'),
('OM005','Salmon',1,300000,4,'M0003'),

('OM006','Caesar Salad',1,85000,5,'M0005'),
('OM007','Beefsteak',2,250000,6,'M0001'),
('OM008','Pasta',1,120000,7,'M0002'),
('OM009','Red Wine',3,150000,8,'M0004'),
('OM010','Pasta',1,120000,9,'M0002'),

('OM011','Beefsteak',2,250000,10,'M0001'),
('OM012','Beefsteak',1,250000,11,'M0001'),
('OM013','Pasta',2,120000,12,'M0002'),
('OM014','Red Wine',1,150000,13,'M0004'),
('OM015','Caesar Salad',1,85000,15,'M0005');
INSERT INTO Invoice
(total_price, invoice_status, order_id, staff_id)
VALUES
(85000,'PAID',5,'S0006'),
(770000,'PAID',10,'S0006'),
(85000,'PAID',15,'S0007'),

(150000,'PENDING',4,'S0006'),
(120000,'PENDING',9,'S0007'),

(250000,'REFUNDED',11,'S0006');
INSERT INTO StaffOrder VALUES
('S0004',NOW(),'PREPARING',3),
('S0004',NOW(),'READY',4),
('S0005',NOW(),'PREPARING',8),
('S0005',NOW(),'READY',14);