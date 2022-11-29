// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.7.0 <0.9.0;

contract Store {
    struct Person {
        address addr;
        uint profit;
    }

    Person developer;
    Person seller;
    Person buyer;

    event Sale(uint itemId, address indexed seller, address indexed buyer, uint price, bool isLocked); // after buy event, log info
    event TimeExpired(uint itemId, address indexed seller, address indexed buyer); // after sealed time expired then
    event Refund(uint itemId, address indexed seller, address indexed buyer); // if buyer click cancel button, deposited ether will return to buyer.
    // if buyer click confirm button, then developer will get 1%, seller 99% ether
    event Confirm(uint itemId, address indexed seller, address indexed buyer, uint price, uint fee, uint change, bool isLocked); 

    struct Product {
        uint itemId;
        address addr;
        uint paid; // paid ether
        uint price; // 99% of real price
        uint fee; // 1% of real price
        uint change; // paid - 100% real price
        bool isLocked; // to seal ether, if seller buy product then, locked;
    }

    mapping(uint => Product) sales; // itemId mapping to Product structrue
    mapping(address => uint) lockTime; // to write down sealing time.

    Product[] salesInfo;
    uint itemIndex = 0;

    modifier buyerCheck() {
        require (msg.sender != developer.addr, "Developer!");
        require(msg.sender != seller.addr, "Seller!");
        require(msg.sender == buyer.addr, "Only Buyer!");
        _;
    }

    constructor() {
        developer = Person(msg.sender, 0);
    }

    // only buyer call this function
    function buy(uint _itemId, uint _price) public buyerCheck() payable returns (bool success) {
        require(msg.value > 0, "Ethers must more than zero!");
        require(msg.sender.balance >= msg.value, "Not enough Ethers!");

        uint price = _price * 10 ** 18; // wei expression
        require(msg.value > price, "Need More Ethers!");

        uint fee = price / 100 * 1; // 1% fee
        uint cost = price - fee; // 99% real price
        uint change = msg.value - price; // value - 100% price
        bool isLocked = true;

        lockTime[msg.sender] = block.timestamp + 3 days; // seal during 3 days.
        sales[_itemId] = Product(_itemId, msg.sender, msg.value, cost, fee, change, isLocked);
        emit Sale(_itemId, seller.addr, msg.sender, cost, isLocked);
        return true;
    }

    function comfirm(uint _itemId) public buyerCheck() payable returns (bool success) {
        require(sales[_itemId].isLocked == true, "Buy First!");
        sales[_itemId].isLocked = false; // unlock

        payable(developer.addr).transfer(sales[_itemId].fee);
        payable(seller.addr).transfer(sales[_itemId].price);
        payable(msg.sender).transfer(sales[_itemId].change);

        seller.profit += sales[_itemId].price;
        developer.profit += sales[_itemId].fee;
        
        emit Confirm(sales[_itemId].itemId, seller.addr, sales[_itemId].addr, sales[_itemId].price, 
        sales[_itemId].fee, sales[_itemId].change, sales[_itemId].isLocked);

        return true;
    }

    function refund(uint _itemId) public buyerCheck() payable returns (bool status) {
        require(sales[_itemId].addr == msg.sender, "Not Purchased!");
        require(sales[_itemId].isLocked == true, "Product Delivered!");
        if(block.timestamp > lockTime[msg.sender]) {
            payable(msg.sender).transfer(sales[_itemId].paid);
            emit TimeExpired(_itemId, seller.addr, msg.sender);
        }
        else {
            payable(msg.sender).transfer(sales[_itemId].paid);
            emit Refund(_itemId, seller.addr, msg.sender);
        }
        return true;
    }

    /* getter */
    function getDeveloperInfo() public view returns(address, uint) {
        return (developer.addr, developer.profit);
    }

    function getSellerInfo() public view returns(address, uint) {
        return (seller.addr, seller.profit);
    }

    function getBuyerAddress() public view returns(address) {
        return buyer.addr;
    }

    function getBuyerByItemID(uint _itemId) public view returns(address) {
        require(sales[_itemId].isLocked == false, "Not Yet Confirmed!");
        return sales[_itemId].addr;
    }

    function getItemInfo(uint _itemId) public returns(uint Id, address _buyer, uint _price, bool _isLocked) {
        require(sales[_itemId].isLocked == false, "Not Yet Confirmed!");
        salesInfo.push(sales[_itemId]);
        itemIndex = salesInfo.length - 1;
        return (salesInfo[itemIndex].itemId, salesInfo[itemIndex].addr, salesInfo[itemIndex].price, _isLocked); 
    }

    // setter
    function setSeller(address _seller) public {
        require(_seller != developer.addr, "Developer!");
        seller.addr = _seller;
    }

    function setBuyer(address _buyer) public {
        require(_buyer != developer.addr, "Developer!");
        require(_buyer != seller.addr, "Seller!");
        buyer.addr = _buyer;
    }
}