
function StockSelector({selectedStock,setSelectedStock}){
    return(
        <>
            <div>
                <label htmlFor="stockSelector">Select a Stock:</label>
                <select  id="stockSelector" value={selectedStock} onChange={(event)=>{
                    setSelectedStock(event.target.value);
                }}>
                    
                    <option value="DairyMilk">DairyMilk</option>
                    <option value="5Star">5Star</option>
                    <option value="FerreroRocher">FerreroRocher</option>
                    <option value="KinderJoy">KinderJoy</option>
                </select>
                <br/>
                <hr/>
            </div>
        </>
    )
}

export default StockSelector;