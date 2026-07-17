function OrderBook({showOrderBook,loadData,OrderBookData}){
    console.log(OrderBookData);
    return (
        <>
        <div>
            <button onClick={()=>{
                loadData();
            }}
            >View OrderBook</button>

        </div> 
        <div className="OrderBookContainer">
            {
                showOrderBook&& 
                    <pre>
                        {JSON.stringify(OrderBookData,null,2)}
                    </pre>
            }
        </div>
        </>
    )
}

export default OrderBook;