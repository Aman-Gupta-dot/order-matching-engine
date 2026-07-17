import { useState } from "react";

function OrderForm({placeOrder,selectedStock,placeOrderResponse}){
    const[side,setSide]=useState("BUY");
    const[type,setType]=useState("LIMIT");
    const[price,setPrice]=useState(0);
    const[quantity,setQuantity]=useState(0);
    
    return (
        <>
        <div>
            <div>
                <h2>Place Order</h2>
            </div>
            <div>
                <form>
                    <label htmlFor="Side">Side:</label>
                    <select value={side} onChange={(event)=>{
                        setSide(event.target.value);
                    }}>
                    
                    <option name="BUY">BUY</option>
                    <option name="SELL">SELL</option>
                </select>
                <br/>
                <br/>
                <label htmlFor="Type">OrderType:</label>
                    <select value={type} onChange={(event)=>{
                        setType(event.target.value);
                    }}>
                    
                    <option name="LIMIT">LIMIT</option>
                    <option name="MARKET">MARKET</option>
                    <option name="FOK">FOK</option>
                    <option name="IOC">IOC</option>
                </select>
                <br/>
                <br/>

                <label htmlFor="Price">Price:</label>
                    <input type="number" value={price} onChange={(event)=>{
                        setPrice(Number(event.target.value));
                    }}></input>
                <br/>
                <br/>

                    <label htmlFor="Quantity">Quantity:</label>
                    <input type="number" value={quantity} onChange={(event)=>{
                        setQuantity(Number(event.target.value));
                    }}></input>
                    <br/>
                    <br/>

                    <button type="submit" onClick={(event)=>{
                        event.preventDefault();
                            const order={
                                stockName:selectedStock,
                                side:side,
                                type:type,
                                price:price,
                                quantity:quantity
                            }
                            placeOrder(order);
                    }}>Place Order</button>
                </form>

                <br/>
                <hr/>
                
            </div>
            <div className="placeOrderResp">
                <pre>
                    {JSON.stringify(placeOrderResponse,null,2)}
                </pre>
            </div>
            <br/>
            <br/>
            <hr/>
        </div> 
        </>
    )
}

export default OrderForm;