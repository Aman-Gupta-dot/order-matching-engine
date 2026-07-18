function OrderBook({showOrderBook,loadData,OrderBookData}){
    return (
        <>
        <div className="flex gap-5 justify-between">
            
                <table>
                    <thead>
                        <h1>BUY</h1>
                        <tr className="flex gap-3 text-xl">
                            <th>Price</th>
                            <th>Quantity</th>
                        </tr>
                    </thead>
                    <tbody>
                    
                    {
                            OrderBookData!=null &&
                            OrderBookData.buyLevels.map((priceAndQty)=>{
                                return(
                                    <tr>
                                        <td>{priceAndQty.priceLevel}</td>
                                        <td>{priceAndQty.totalQuantity}</td>
                                    </tr>
                                )
                            })
                    }
                    
                    </tbody>
                    
            </table>
            <table>
                    
                    <thead>
                        <h1>SELL</h1>
                        <tr className="flex gap-3 text-xl">
                            <th>Price</th>
                            <th>Quantity</th>
                        </tr>
                    </thead>
                    <tbody>
                    
                    {
                            OrderBookData!=null &&
                            OrderBookData.sellLevels.map((priceAndQty)=>{
                                return(
                                    <tr>
                                        <td>{priceAndQty.priceLevel}</td>
                                        <td>{priceAndQty.totalQuantity}</td>
                                    </tr>
                                )
                            })
                    }
                    
                    </tbody>
                    
            </table>      
            
        </div>
        </>
    )
}

export default OrderBook;