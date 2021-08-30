// ----------- Line Graph Representation -----------------------------
google.charts.load('current', {'packages':['corechart']});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {
    var data = google.visualization.arrayToDataTable( line_graph_data() );

    var options = {
        title: 'Humidity and Temparature',
        curveType: 'function',
        legend: { position: 'bottom' }
    };

    var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));

    chart.draw(data, options);
}

// ----------- Bar Graph Representation -----------------------------


google.load("visualization", "1", {packages:["corechart"]});
    google.setOnLoadCallback(drawChart1);
    function drawChart1() {
    var data = google.visualization.arrayToDataTable( bar_graph_data() );

    var options = {
        title: 'Total Useage of Pumps',
        hAxis: {title: 'Year', titleTextStyle: {color: 'red'}}
    };

    var chart = new google.visualization.ColumnChart(document.getElementById('chart_div1'));
    chart.draw(data, options);
    }

//    ----------- Table Representation -----------------------------

// google.charts.load('current', {'packages':['table']});
// google.charts.setOnLoadCallback(drawTable);

// function drawTable() {
//     var data = new google.visualization.DataTable();
//     data.addColumn('string', 'Name');
//     data.addColumn('number', 'Salary');
//     data.addColumn('boolean', 'Full Time Employee');
//     data.addRows( table_data() );

//     var table = new google.visualization.Table(document.getElementById('table_div'));

//     table.draw(data, {showRowNumber: true, width: '100%', height: '100%', title: 'Pump On Count',});
// }

$(window).resize(function(){
    drawChart();
    drawChart1();
    // drawTable();
});