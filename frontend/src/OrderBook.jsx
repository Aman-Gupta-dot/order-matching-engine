function OrderBook({showOrderBook,loadData,OrderBookData}){
    return (
        <>
        <div className="OrderBookContainer">
            
                <table>
                    <thead>
                        <tr className="flex gap-5 text-xl">
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
            
        </div>
        </>
    )
}

export default OrderBook;