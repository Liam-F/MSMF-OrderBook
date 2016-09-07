# MSMF-Course-Projects  
In modern financial markets, market makers (dealers) are agents who stand ready to buy
and sell securities. Market makers are remunerated for their services by being able to “buy
low and sell high”. Instead of a single price at which any trade can occur, dealers quote two
prices – a “bid” (dealer’s purchase, customer’s sale) and an “ask” (dealer’s sale, customer’s
purchase). The ask price is higher than the bid price, and the difference between the two is
called the spread – the dealer’s source of revenue.

An electronic exchange uses limit orders and employs no designated middlemen. All liquidity
comes from customers’ limit orders that are arranged in order books (essentially two
priority queues ordered by price) as shown in following figure (a) (limit price – number
of shares). Priority is given to those participants who placed their order first.
 
The main body of our orderbook system is  two list--- the list contains outstanding selling orders and the list contian outstanding buying orders. Each time an order comes in, it has to through the process shown in the picture above.
 
For programming part, I seperate the whole program into 3 parts:
 
#1. Orderbook class: saves the order-book (buy and sell list ) in its private data structure, perform the  transaction process abve and call the function of message class.
#2. Message class: each time an operation is made, such as order received from a broker, an transaction is made with a counterparty, order is returned due to some reason, an notification is sent.
#3. Main body: receives the order, call the order class.
#4. Order class: contain the information of an order like amount, bid/offer price, counter party name, etc and being able to change its amount after a transaction.  

