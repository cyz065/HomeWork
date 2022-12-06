// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.7.0 <0.9.0;

contract Store {
    mapping(uint => address) account; // set account
    mapping(address => uint) balances; // balances of each account
    mapping(uint => Product) sales; // itemId mapping to Product
    mapping(address => uint) lockTime; // to write down locked time.

    constructor() {
        account[0] = msg.sender; // set developer who will get 1% fee
        balances[msg.sender] = 0;
    }
    Product[] salesInfo; // store selled items information

    
    event Sale(uint itemId, address indexed seller, address indexed buyer, uint price, bool isLocked); // after buy event
    event TimeExpired(uint itemId, address indexed seller, address indexed buyer); // after locked time expired
    event Cancel(uint itemId, address indexed seller, address indexed buyer); // if buyer click cancel button, deposit ether will return to buyer.
    // if buyer click confirm button, then developer will get 1%, seller 99% etehr
    event Confirm(uint itemId, address indexed seller, address indexed buyer, uint price, uint fee, uint change, bool isLocked);
    event Info(uint itemId, address indexed buyer, uint price, bool isLocked);

    struct Product {
        string name;
        uint year;
        uint itemId;
        address addr; // address who bought item corresponding to the itemId.
        uint paid; // paid ether 100%
        uint price; // 99% of real price
        uint fee; // 1% of real price
        uint change; // paid - 100% real price
        bool isLocked; // to seal ether, if seller buy product then, locked;
        bool isSold; // check sold or not
    }

    uint itemIndex = 0;

    modifier buyerCheck() {
        require(account[1] != 0x0000000000000000000000000000000000000000, "Set Seller First!");
        require(msg.sender != 0x0000000000000000000000000000000000000000, "Set Buyer!");
        require (msg.sender != account[0], "Developer!");
        require(msg.sender != account[1], "Seller!");
        require(msg.sender == account[2], "Only Buyer!");
        _;
    }

    // only buyer call this function
    function buy(string memory _name, uint _year, uint _itemId, uint _price) public buyerCheck() payable returns (bool success) {
        require(sales[_itemId].isSold == false, "Already Purchased Item!");
        require(msg.value > 0, "Price must more than zero!");
        require(msg.sender.balance >= msg.value, "Account have not enough Ethers!");

        uint price = _price * 10 ** 18; // wei expression
        require(msg.value > price, "Need More Ethers!");

        uint fee = price / 100 * 1; // 1% fee
        uint cost = price - fee; // 99% real price
        uint change = msg.value - price; // value - 100% price
        bool isLocked = true;

        lockTime[msg.sender] = block.timestamp + 3 days; // seal during 3 days.
        sales[_itemId] = Product(_name, _year, _itemId, msg.sender, msg.value, cost, fee, change, isLocked, true);
        emit Sale(_itemId, account[1], msg.sender, cost, isLocked);
        return true;
    }

    function comfirm(uint _itemId) public buyerCheck() payable returns (bool success) {
        require(sales[_itemId].addr != 0x0000000000000000000000000000000000000000, "Buy First!");
        require(sales[_itemId].isSold == true, "Buy First!");
        sales[_itemId].isLocked = false; // unlock

        payable(account[0]).transfer(sales[_itemId].fee);
        payable(account[1]).transfer(sales[_itemId].price);
        payable(msg.sender).transfer(sales[_itemId].change);

        balances[account[0]] += sales[_itemId].fee;
        balances[account[1]] += sales[_itemId].price;
        
        emit Confirm(sales[_itemId].itemId, account[1], sales[_itemId].addr, sales[_itemId].price, 
        sales[_itemId].fee, sales[_itemId].change, sales[_itemId].isLocked);

        return true;
    }

    // after 3days
    function refund(uint _itemId) public buyerCheck() payable returns (bool status) {
        require(sales[_itemId].addr != 0x0000000000000000000000000000000000000000, "Buy First!");
        require(sales[_itemId].addr == msg.sender, "Not Buyer!");
        require(sales[_itemId].isSold == true, "Not Purchased!");
        require(sales[_itemId].isLocked == true, "Product Delivered!");
        require(block.timestamp > lockTime[msg.sender], "After 3 Days!");

        if(block.timestamp > lockTime[msg.sender]) {
            sales[_itemId].addr = 0x0000000000000000000000000000000000000000;
            sales[_itemId].isSold = false;

            payable(msg.sender).transfer(sales[_itemId].paid);
            emit TimeExpired(_itemId, account[1], msg.sender);
        }
        return true;
    }

    // just buyer cancel before 3 days
    function cancel(uint _itemId) public buyerCheck() payable returns (bool status) {
        require(sales[_itemId].addr != 0x0000000000000000000000000000000000000000, "Buy First!");
        require(sales[_itemId].addr == msg.sender, "Not Purchased!");
        require(sales[_itemId].isLocked == true, "Product Delivered!");
        require(sales[_itemId].isSold == true," Buy First");

        if(block.timestamp < lockTime[msg.sender]) {
            sales[_itemId].addr = 0x0000000000000000000000000000000000000000;
            sales[_itemId].isSold = false;
            payable(msg.sender).transfer(sales[_itemId].paid);
            emit Cancel(_itemId, account[1], msg.sender);
        }
        return true;
    }

    /* getter */
    function getDeveloperInfo() public view returns(address, uint) {
        return (account[0], balances[account[0]]);
    }

    function getSellerInfo() public view returns(address, uint) {
        return (account[1], balances[account[1]]);
    }

    function getBuyerAddress() public view returns(address) {
        return account[2];
    }

    function getBuyerByItemID(uint _itemId) public view returns(address) {
        require(sales[_itemId].addr != 0x0000000000000000000000000000000000000000, "Not Yet Bought");
        require(sales[_itemId].isLocked == false, "Not Yet Confirmed!");
        return sales[_itemId].addr;
    }

    function getItemInfo(uint _itemId) public returns(uint Id, address _buyer, uint _price, bool _isLocked) {
        require(sales[_itemId].addr != 0x0000000000000000000000000000000000000000, "Not Yet Bought");
        require(sales[_itemId].isLocked == false, "Not Yet Confirmed!");

        salesInfo.push(sales[_itemId]);
        itemIndex = salesInfo.length - 1;
        emit Info(salesInfo[itemIndex].itemId, salesInfo[itemIndex].addr, salesInfo[itemIndex].price, _isLocked);
        return (salesInfo[itemIndex].itemId, salesInfo[itemIndex].addr, salesInfo[itemIndex].price, _isLocked); 
    }

    // setter
    function setSeller(address _seller) public {
        require(_seller != 0x0000000000000000000000000000000000000000, "Set Seller!");
        require(_seller != account[0], "Developer!");
        account[1] = _seller;
    }

    function setBuyer(address _buyer) public {
        require(_buyer != 0x0000000000000000000000000000000000000000, "Set Buyer!");
        require(_buyer != account[0], "Developer!");
        require(_buyer != account[1], "Seller!");
        account[2] = _buyer;
    }
}