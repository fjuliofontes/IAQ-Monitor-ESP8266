import datetime
import csv

import dash
import dash_core_components as dcc
import dash_html_components as html
import plotly
import plotly.graph_objects as go
from dash.dependencies import Input, Output

def get_data(timestamp):
    # more or less 3 seconds
    upLimit = timestamp + datetime.timedelta(seconds=3)
    downLimit = timestamp - datetime.timedelta(seconds=3)

    with open('bme680.csv', mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        lastRow = []
        for row in csv_reader:
            # search desired timestamp
            read_timestamp = datetime.datetime.fromtimestamp(int(row["timestamp"]))
            if( (read_timestamp <= upLimit) and (read_timestamp >= downLimit) ):
                return row
            # save last row
            lastRow = row

    return lastRow

def get_data_from_interval(start_timestamp,stop_timestamp):
    # more or less 3 seconds
    upLimit = stop_timestamp + datetime.timedelta(seconds=3)
    downLimit = start_timestamp - datetime.timedelta(seconds=3)

    with open('bme680.csv', mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        rows = []
        for row in csv_reader:
            # search desired timestamp
            read_timestamp = datetime.datetime.fromtimestamp(int(row["timestamp"]))
            if( (read_timestamp <= upLimit) and (read_timestamp >= downLimit) ):
                rows.append(row)

    return rows
            

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.layout = html.Div(
    html.Div([
        html.H4('Indoor Air Quality (BME680 based)'),
        #html.Div(id='live-update-text'),
        dcc.Graph(id='gauge-indicators'),
        dcc.Graph(id='live-update-graph'),
        dcc.Interval(
            id='interval-component',
            interval= 1*1000, # in milliseconds
            n_intervals=0
        )
    ])
)

# Update Interval as soon we have n samples
@app.callback(Output('interval-component', 'interval'),
              Input('interval-component', 'n_intervals'))
def update_interval(n):
    if(n > 10):
        # return 1 * 60 * (1*1000)
        return 1000
    else:
        return 1000

# @app.callback(Output('live-update-text', 'children'),
#               Input('interval-component', 'n_intervals'))
# def update_metrics(n):
#     row = get_data(datetime.datetime.now())
#     style = {'padding': '5px', 'fontSize': '16px'}
#     return [
#         html.Span('Temperature: ' + row["T"], style=style),
#         html.Span('Humidity: ' + row["H"], style=style),
#         html.Span('Pressure: ' + row["P"], style=style)
#     ]


# Multiple components can update everytime interval gets fired.
@app.callback(Output('live-update-graph', 'figure'),
              Input('interval-component', 'n_intervals'))
def update_graph_live(n):
    data = {
        'time': [],
        'T': [],
        # 'rawT': [],
        'H': [],
        # 'rawH': [],
        'P': [],
        'IAQ' :  [],
        # 'sIAQ' :  [],
        'eCO2' : [],
        'eVOC' : []
    }

    # Collect some data [from last hour until now]
    # 1611599124,19.880,19.815,76.883,77.204,1001.780,120.740,100.972,1009.720,1.577
    # 1611600255,19.830,19.765,76.903,77.249,1002.030,120.027,99.427,994.271,1.540
    rows = get_data_from_interval(datetime.datetime.now()-datetime.timedelta(seconds=15*60),datetime.datetime.now())

    for row in rows:
        data['time'].append(datetime.datetime.fromtimestamp(int(row["timestamp"])))
        data['T'].append(float(row["T"]))
        #data['rawT'].append(float(row["rawT"]))
        data['H'].append(float(row["H"]))
        #data['rawH'].append(float(row["rawH"]))
        data['P'].append(float(row["P"]))
        data['IAQ'].append(float(row["IAQ"]))
        #data['sIAQ'].append(float(row["sIAQ"]))
        data['eCO2'].append(float(row["eCO2"]))
        data['eVOC'].append(float(row["eVOC"]))

    # Create the graph with subplots
    fig =  plotly.subplots.make_subplots(
        subplot_titles=(
            "Temperature", 
            "Humidity",
            "Pressure", 
            "IAQ index",
            "Equivalent CO2",
            "Equivalent VOC"
        ),
        rows=6, 
        cols=1,
        vertical_spacing=0.05)
    
    # fig = plotly.tools.make_subplots(rows=3, cols=1, vertical_spacing=0.2)
    # fig['layout']['margin'] = {
    #     'l': 30, 'r': 10, 'b': 30, 't': 10
    # }
    
    #fig['layout']['legend'] = {'x': 0, 'y': 0, 'xanchor': 'center'}
    
    fig.append_trace(
        {
            'x': data['time'],
            'y': data['T'],
            #'text': data['time'],
            'name': 'Temperature',
            'mode': 'lines',
            'type': 'scatter'
        },
        row=1, 
        col=1
    )
    
    # fig.append_trace(
    #     {
    #         'x': data['time'],
    #         'y': data['rawT'],
    #         #'text': data['time'],
    #         'name': 'Raw Temperature',
    #         'mode': 'lines',
    #         'type': 'scatter'
    #     },
    #     row=1, 
    #     col=1
    # )

    fig.append_trace(
        {
            'x': data['time'],
            'y': data['H'],
            #'text': data['time'],
            'name': 'Humidity',
            'mode': 'lines',
            'type': 'scatter'
        }, 
        row=2, 
        col=1
    )

    # fig.append_trace(
    #     {
    #         'x': data['time'],
    #         'y': data['rawH'],
    #         #'text': data['time'],
    #         'name': 'Raw Humidity',
    #         'mode': 'lines',
    #         'type': 'scatter'
    #     }, 
    #     row=2, 
    #     col=1
    # )

    fig.append_trace(
        {
            'x': data['time'],
            'y': data['P'],
            'name': 'Pressure',
            'mode': 'lines',
            'type': 'scatter'
        }, 
        row=3, 
        col=1
    )

    fig.append_trace(
        {
            'x': data['time'],
            'y': data['IAQ'],
            #'text': data['time'],
            'name': 'IAQ',
            'mode': 'lines',
            'type': 'scatter'
        },
        row=4, 
        col=1
    )

    # fig.append_trace(
    #     {
    #         'x': data['time'],
    #         'y': data['sIAQ'],
    #         #'text': data['time'],
    #         'name': 'Static IAQ',
    #         'mode': 'lines',
    #         'type': 'scatter'
    #     },
    #     row=4, 
    #     col=1
    # )

    fig.append_trace(
        {
            'x': data['time'],
            'y': data['eCO2'],
            #'text': data['time'],
            'name': 'eCO2',
            'mode': 'lines', # + markers
            'type': 'scatter'
        }, 
        row=5, 
        col=1
    )

    fig.append_trace(
        {
            'x': data['time'],
            'y': data['eVOC'],
            #'text': data['time'],
            'name': 'eVOC',
            'mode': 'lines',
            'type': 'scatter'
        }, 
        row=6, 
        col=1
    )

    # Update xaxis properties
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=1, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=2, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=3, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=4, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=5, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=6, col=1)

    # Update yaxis properties
    fig.update_yaxes(title_text="Celsius", row=1, col=1)
    fig.update_yaxes(title_text="Percentage", row=2, col=1)
    fig.update_yaxes(title_text="hPascal", row=3, col=1)
    fig.update_yaxes(title_text="Index", row=4, col=1)
    fig.update_yaxes(title_text="PPM", row=5, col=1)
    fig.update_yaxes(title_text="PPM", row=6, col=1)

    fig.update_layout(
        height=2000, 
        width=None, 
        title_text="Graphical Visualization",
        showlegend=True
    )

    return fig

# Multiple components can update everytime interval gets fired.
@app.callback(Output('gauge-indicators', 'figure'),
              Input('interval-component', 'n_intervals'))
def update_graph_live(n):
    current = get_data(datetime.datetime.now())
    last = get_data(datetime.datetime.now()-datetime.timedelta(seconds=30))

    fig = go.Figure()

    fig.add_trace(
        go.Indicator(
            domain = {'row': 0, 'column': 1},
            value = float(current["IAQ"]),
            mode = "gauge+number+delta",
            title = {'text': "IAQ",'font': {'size': 24}},
            delta = {
                'reference': float(last["IAQ"]),
                'increasing': {'color': "red"},
                'decreasing': {'color': "green"}
            },
            gauge = {
                'axis': {
                    'range': [0, 351],
                    'tickwidth': 1, 
                    'tickcolor': "darkblue"
                },
                'borderwidth': 2,
                'bordercolor': "gray",
                'bar': {'color': "green"},
                'steps' : [
                    {'range': [0, 50], 'color': "#00e400"},
                    {'range': [51, 100], 'color': "#92d050"},
                    {'range': [101, 150], 'color': "#ffff02"},
                    {'range': [151, 200], 'color': "#ff7e00"},
                    {'range': [201, 250], 'color': "#ff0000"},
                    {'range': [251, 350], 'color': "#99004c"},
                    {'range': [351, None], 'color': "#663300"}
                ],
                'threshold' : {
                    'line': {'color': "red", 'width': 4}, 'thickness': 0.9, 'value': 175}
                }
        )
    )

    fig.add_trace(
        go.Indicator(
            domain = {'row': 0, 'column': 0},
            value = float(current["T"]),
            mode = "gauge+number+delta",
            title = {'text': "Temperature",'font': {'size': 24}},
            delta = {
                'reference': float(last["T"]),
                'increasing': {'color': "green"},
                'decreasing': {'color': "red"}
            },
            gauge = {
                'axis': {
                    'range': [0, 30],
                    'tickwidth': 1, 
                    'tickcolor': "darkblue"
                },
                'borderwidth': 2,
                'bordercolor': "gray",
                'bar': {'color': "green"},
                'steps' : [
                    {'range': [0, 10], 'color': "#ff0000"},
                    {'range': [10.1, 15], 'color': "#ffff02"},
                    {'range': [15.1, 25], 'color': "#00e400"},
                    {'range': [25.1, 30], 'color': "#ff7e00"}
                ]
            }
        )
    )

    fig.add_trace(
        go.Indicator(
            domain = {'row': 0, 'column': 2},
            value = float(current["H"]),
            mode = "gauge+number+delta",
            title = {'text': "Humidity",'font': {'size': 24}},
            delta = {
                'reference': float(last["H"]),
                'increasing': {'color': "red"},
                'decreasing': {'color': "green"}
            },
            gauge = {
                'axis': {
                    'range': [0, 100],
                    'tickwidth': 1, 
                    'tickcolor': "darkblue"
                },
                'borderwidth': 2,
                'bordercolor': "gray",
                'bar': {'color': "blue"},
                'steps' : [
                    {'range': [0, 25], 'color': "#99f4ff"},
                    {'range': [25.1, 50], 'color': "#7cdffd"},
                    {'range': [50.1, 75], 'color': "#5bcff7"},
                    {'range': [75.1, 100], 'color': "#46b1ef"}
                ]
            }
        )
    )

    fig.update_layout(
        grid = {'rows': 1, 'columns': 3, 'pattern': "independent"}
    )

    return fig

if __name__ == '__main__':
    app.run_server(debug=True)
