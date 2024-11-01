import axios from 'axios';
import Chart from 'chart.js/auto';
const apiURL = 'http://localhost:18080/api/'

const expensesChart = document.getElementById('expenses-chart');
const budgedChart = document.getElementById('budged-chart');
document.addEventListener("DOMContentLoaded", (event) => {
    let userId = localStorage.getItem('userId'); 
    if(userId == -1 || userId == null || userId == undefined || userId == "undefined")
    {
        location.replace('../index.html');
    }
});

initData();

function initData()
{
    getUserData();
    initCharts();
}

function getUserData()
{
    axios.get(apiURL + `user/getUserData/${localStorage.getItem('userId')}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                document.getElementById('welcome-name').innerText = ` ${response.data.userName}`
            }
        }
        else
        {
            console.log(error);
            alert("Unauthorised");
        }
    })
    .catch(function (error) {
        console.log(error);
        alert("Fatal error");
    });
}

function initCharts()
{
    initExpenseChart();
    initBudgetChart();
}

function initExpenseChart()
{
    axios.get(apiURL + `graph/getExpenseGraph/${localStorage.getItem('userId')}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log(response.data);

                new Chart(budgedChart, {
                    type: 'bar',
                    data: {
                      labels: response.data.date,
                      datasets: [{
                        label: 'Expenses',
                        data: response.data.sum,
                        borderWidth: 1
                      }]
                    },
                    options: {
                        legend: {
                            position: 'top',
                          },
                          title: {
                            display: true,
                            text: 'Expenses'
                          },
                      scales: {
                        y: {
                          beginAtZero: true
                        }
                      }
                    }
                });         
            }
        }
        else
        {
            console.log(error);
            alert("Unauthorised");
        }
    })
    .catch(function (error) {
        console.log(error);
        alert("Fatal error");
    });
}

function initBudgetChart()
{
    axios.get(apiURL + `graph/getBudetGraph/${localStorage.getItem('userId')}/Fee`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log(response.data);
                new Chart(expensesChart, {
                    data: {
                      datasets: [{
                        label: 'Budget',
                        data: response.data.budgetAmount,
                        type: 'line'
                      },
                      {
                        label: 'Expenses',
                        data: response.data.sum,
                        type: 'bar'
                      }
                    ],
                    labels: response.data.date,

                    },
                    options: {
                         responsive: true,
                        legend: {
                            position: 'top',
                          },
                          title: {
                            display: true,
                            text: 'Expenses'
                          },
                    }
                });         
            }
        }
        else
        {
            console.log(error);
            alert("Unauthorised");
        }
    })
    .catch(function (error) {
        console.log(error);
        alert("Fatal error");
    });
}