function OrderBook({showOrderBook,loadData,OrderBookData}){
    return (
        <>
        <div className="flex  gap-5 justify-between mt-4 h-60 overflow-y-auto  scrollbar pr-2">
            <div className="flex flex-col">
                <h1>BUY</h1>
                <table>
                    
                    <thead>
                        
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
                                    
                                        <tr key={priceAndQty.priceLevel}>
                                        <td>{priceAndQty.priceLevel}</td>
                                        <td>{priceAndQty.totalQuantity}</td>
                                        </tr>
                                    
                                )
                            })
                    }
                    
                    </tbody>
                    
            </table>
            </div>
            <div className="flex flex-col">
                <h1>SELL</h1>
            <table>
                    
                    <thead>
                        
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
                                    

                                        <tr key={priceAndQty.priceLevel}>
                                        <td>{priceAndQty.priceLevel}</td>
                                        
                                        <td>{priceAndQty.totalQuantity}</td>
                                    </tr>
                                    
                                )
                            })
                    }
                    
                    </tbody>
                    
            </table> 
            </div>     
            
        </div>
        </>
    )
}

export default OrderBook;