SET FOREIGN_KEY_CHECKS = 1;
use restaurantordermanagement;
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
('Min','0910000005'),
('Nguyen Van An', '0910000006'),
('Tran Bao Ngoc', '0910000007'),
('Le Tuan Tu', '0910000008'),
('Pham Thi Hang', '0910000009'),
('Hoang Van Minh', '0910000010'),
('Doan Thi Mai', '0910000011'),
('Vu Tuan Kiet', '0910000012'),
('Dang Thuy Tram', '0910000013'),
('Bui Van Long', '0910000014'),
('Do Thi Lan', '0910000015'),
('Ho Quang Hieu', '0910000016'),
('Ngo Kien Huy', '0910000017'),
('Ly Hai', '0910000018'),
('Tran Thanh', '0910000019'),
('Hari Won', '0910000020'),
('Truong Giang', '0910000021'),
('Nha Phuong', '0910000022'),
('Miu Le', '0910000023'),
('Karik', '0910000024'),
('Binz', '0910000025'),
('Suboi', '0910000026'),
('Rhymastic', '0910000027'),
('JustaTee', '0910000028'),
('Wowy', '0910000029'),
('Toc Tien', '0910000030'),
('Dong Nhi', '0910000031'),
('Ong Cao Thang', '0910000032'),
('Noo Phuoc Thinh', '0910000033'),
('Bich Phuong', '0910000034'),
('Issac', '0910000035');

INSERT INTO MenuItem VALUES
('M0001','Beefsteak',250000,'Main dish',1),
('M0002','Pasta',120000,'Main dish',1),
('M0003','Salmon',300000,'Side dish',1),
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
(1,370000,'','CREATED','Son Tung','S0002',1),
(2,270000,'','PENDING','Jack','S0002',2),
(3,250000,'','PREPARING','My Tam','S0003',3),
(4,450000,'','READY','Den Vau','S0003',4),
(5,85000,'','COMPLETED','Min','S0002',5),
(6, 250000, 'Chin vua', 'COMPLETED', 'Nguyen Van An', 'S0002', 6),
(7, 270000, '', 'PENDING', 'Tran Bao Ngoc', 'S0006', 7),
(8, 300000, 'Khong hanh', 'PREPARING', 'Le Tuan Tu', 'S0003', 8),
(1, 150000, '', 'READY', 'Pham Thi Hang', 'S0002', 9),
(2, 420000, '', 'COMPLETED', 'Hoang Van Minh', 'S0008', 10),
(5, 120000, 'Mang ve', 'CREATED', 'Doan Thi Mai', 'S0002', 11),
(9, 550000, '', 'READY', 'Vu Tuan Kiet', 'S0003', 12),
(10, 85000, '', 'COMPLETED', 'Dang Thuy Tram', 'S0006', 13),
(3, 300000, 'Gap', 'PENDING', 'Bui Van Long', 'S0002', 14),
(4, 250000, '', 'COMPLETED', 'Do Thi Lan', 'S0008', 15),
(11, 370000, 'Them sot', 'PREPARING', 'Ho Quang Hieu', 'S0003', 16),
(12, 120000, '', 'READY', 'Ngo Kien Huy', 'S0006', 17),
(6, 450000, '', 'COMPLETED', 'Ly Hai', 'S0002', 18),
(7, 600000, 'Tiep khach', 'PENDING', 'Tran Thanh', 'S0008', 19),
(8, 85000, 'It dau', 'CREATED', 'Hari Won', 'S0006', 20),
(15, 250000, '', 'COMPLETED', 'Truong Giang', 'S0003', 21),
(14, 270000, '', 'COMPLETED', 'Nha Phuong', 'S0002', 22),
(2, 150000, 'Da lanh', 'READY', 'Miu Le', 'S0008', 23),
(5, 300000, '', 'PREPARING', 'Karik', 'S0006', 24),
(9, 500000, '', 'COMPLETED', 'Binz', 'S0003', 25),
(1, 120000, '', 'COMPLETED', 'Suboi', 'S0002', 26),
(3, 235000, '', 'READY', 'Rhymastic', 'S0008', 27),
(10, 450000, '', 'PENDING', 'JustaTee', 'S0003', 28),
(12, 250000, 'Chin ky', 'COMPLETED', 'Wowy', 'S0006', 29),
(4, 85000, '', 'CREATED', 'Toc Tien', 'S0002', 30),
(11, 600000, '', 'COMPLETED', 'Dong Nhi', 'S0008', 31),
(8, 300000, '', 'PREPARING', 'Ong Cao Thang', 'S0003', 32),
(6, 370000, '', 'READY', 'Noo Phuoc Thinh', 'S0006', 33),
(7, 120000, '', 'COMPLETED', 'Bich Phuong', 'S0002', 34),
(15, 250000, '', 'COMPLETED', 'Issac', 'S0008', 35);

INSERT INTO OrderItem VALUES
-- Order 6: 250k
('OM001', 'Beefsteak', 1, 250000, 6, 'M0001'),


('OM001', 'Pasta', 1, 120000, 7, 'M0002'),
('OM002', 'Red Wine', 1, 150000, 7, 'M0004'),

-- Order 8: 300k
('OM001', 'Salmon', 1, 300000, 8, 'M0003'),

-- Order 9: 150k
('OM001', 'Red Wine', 1, 150000, 9, 'M0004'),

-- Order 10: 120k + 300k = 420k
('OM001', 'Pasta', 1, 120000, 10, 'M0002'),
('OM002', 'Salmon', 1, 300000, 10, 'M0003'),

-- Order 11: 120k
('OM001', 'Pasta', 1, 120000, 11, 'M0002'),

-- Order 12: 250k + 300k = 550k
('OM001', 'Beefsteak', 1, 250000, 12, 'M0001'),
('OM002', 'Salmon', 1, 300000, 12, 'M0003'),

-- Order 13: 85k
('OM001', 'Caesar Salad', 1, 85000, 13, 'M0005'),

-- Order 14: 300k
('OM001', 'Salmon', 1, 300000, 14, 'M0003'),

-- Order 15: 250k
('OM001', 'Beefsteak', 1, 250000, 15, 'M0001'),

-- Order 16: 120k + 250k = 370k
('OM001', 'Pasta', 1, 120000, 16, 'M0002'),
('OM002', 'Beefsteak', 1, 250000, 16, 'M0001'),

-- Order 17: 120k
('OM001', 'Pasta', 1, 120000, 17, 'M0002'),

-- Order 18: 300k + 150k = 450k
('OM001', 'Salmon', 1, 300000, 18, 'M0003'),
('OM002', 'Red Wine', 1, 150000, 18, 'M0004'),

-- Order 19: 250k + 300k + 50k (tip/extra assumed to reach 600 or maybe 2 wines) -> Let's do 2 Salmons
('OM001', 'Salmon', 2, 300000, 19, 'M0003'),

-- Order 20: 85k
('OM001', 'Caesar Salad', 1, 85000, 20, 'M0005'),

-- Order 21: 250k
('OM001', 'Beefsteak', 1, 250000, 21, 'M0001'),

-- Order 22: 120k + 150k = 270k
('OM001', 'Pasta', 1, 120000, 22, 'M0002'),
('OM002', 'Red Wine', 1, 150000, 22, 'M0004'),

-- Order 23: 150k
('OM001', 'Red Wine', 1, 150000, 23, 'M0004'),

-- Order 24: 300k
('OM001', 'Salmon', 1, 300000, 24, 'M0003'),

-- Order 25: 250k + 250k = 500k
('OM001', 'Beefsteak', 2, 250000, 25, 'M0001'),

-- Order 26: 120k
('OM001', 'Pasta', 1, 120000, 26, 'M0002'),

-- Order 27: 150k + 85k = 235k
('OM001', 'Red Wine', 1, 150000, 27, 'M0004'),
('OM002', 'Caesar Salad', 1, 85000, 27, 'M0005'),

-- Order 28: 150k + 300k = 450k
('OM001', 'Red Wine', 1, 150000, 28, 'M0004'),
('OM002', 'Salmon', 1, 300000, 28, 'M0003'),

-- Order 29: 250k
('OM001', 'Beefsteak', 1, 250000, 29, 'M0001'),

-- Order 30: 85k
('OM001', 'Caesar Salad', 1, 85000, 30, 'M0005'),

-- Order 31: 300k + 300k = 600k
('OM001', 'Salmon', 2, 300000, 31, 'M0003'),

-- Order 32: 300k
('OM001', 'Salmon', 1, 300000, 32, 'M0003'),

-- Order 33: 250k + 120k = 370k
('OM001', 'Beefsteak', 1, 250000, 33, 'M0001'),
('OM002', 'Pasta', 1, 120000, 33, 'M0002'),

-- Order 34: 120k
('OM001', 'Pasta', 1, 120000, 34, 'M0002'),

-- Order 35: 250k
('OM001', 'Beefsteak', 1, 250000, 35, 'M0001');

INSERT INTO Invoice
(total_price, invoice_status, order_id, staff_id)
VALUES
(85000,'PAID',5,'S0006');
INSERT INTO StaffOrder VALUES
-- Đơn hàng 6: S0002 - COMPLETED
('S0002', NOW(), 'COMPLETED', 6),
-- Đơn hàng 7: S0006 - PENDING
('S0006', NOW(), 'PENDING', 7),
-- Đơn hàng 8: S0003 - PREPARING
('S0003', NOW(), 'PREPARING', 8),
-- Đơn hàng 9: S0002 - READY
('S0002', NOW(), 'READY', 9),
-- Đơn hàng 10: S0008 - COMPLETED
('S0008', NOW(), 'COMPLETED', 10),
-- Đơn hàng 11: S0002 - CREATED
('S0002', NOW(), 'CREATED', 11),
-- Đơn hàng 12: S0003 - PAID (Ghi nhận là COMPLETED trong quy trình)
('S0003', NOW(), 'COMPLETED', 12),
-- Đơn hàng 13: S0006 - COMPLETED
('S0006', NOW(), 'COMPLETED', 13),
-- Đơn hàng 14: S0002 - PENDING
('S0002', NOW(), 'PENDING', 14),
-- Đơn hàng 15: S0008 - COMPLETED
('S0008', NOW(), 'COMPLETED', 15),
-- Đơn hàng 16: S0003 - PREPARING
('S0003', NOW(), 'PREPARING', 16),
-- Đơn hàng 17: S0006 - READY
('S0006', NOW(), 'READY', 17),
-- Đơn hàng 18: S0002 - COMPLETED
('S0002', NOW(), 'COMPLETED', 18),
-- Đơn hàng 19: S0008 - PENDING
('S0008', NOW(), 'PENDING', 19),
-- Đơn hàng 20: S0006 - CREATED
('S0006', NOW(), 'CREATED', 20),
-- Đơn hàng 21: S0003 - COMPLETED
('S0003', NOW(), 'COMPLETED', 21),
-- Đơn hàng 22: S0002 - COMPLETED
('S0002', NOW(), 'COMPLETED', 22),
-- Đơn hàng 23: S0008 - READY
('S0008', NOW(), 'READY', 23),
-- Đơn hàng 24: S0006 - PREPARING
('S0006', NOW(), 'PREPARING', 24),
-- Đơn hàng 25: S0003 - COMPLETED
('S0003', NOW(), 'COMPLETED', 25),
-- Đơn hàng 26: S0002 - COMPLETED
('S0002', NOW(), 'COMPLETED', 26),
-- Đơn hàng 27: S0008 - PAID (Ghi nhận là COMPLETED)
('S0008', NOW(), 'COMPLETED', 27),
-- Đơn hàng 28: S0003 - PENDING
('S0003', NOW(), 'PENDING', 28),
-- Đơn hàng 29: S0006 - COMPLETED
('S0006', NOW(), 'COMPLETED', 29),
-- Đơn hàng 30: S0002 - CREATED
('S0002', NOW(), 'CREATED', 30),
-- Đơn hàng 31: S0008 - COMPLETED
('S0008', NOW(), 'COMPLETED', 31),
-- Đơn hàng 32: S0003 - PREPARING
('S0003', NOW(), 'PREPARING', 32),
-- Đơn hàng 33: S0006 - READY
('S0006', NOW(), 'READY', 33),
-- Đơn hàng 34: S0002 - COMPLETED
('S0002', NOW(), 'COMPLETED', 34),
-- Đơn hàng 35: S0008 - COMPLETED
('S0008', NOW(), 'COMPLETED', 35);
select * from Invoice;
select * from OrderTable;
select * from StaffOrder;