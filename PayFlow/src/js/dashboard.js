import axios from 'axios';
import Chart from 'chart.js/auto';
const apiURL = 'http://localhost:18080/api/'

const expensesChart = document.getElementById('expenses-chart');
const earningsChart = document.getElementById('earnings-chart');
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
    initEarningChart();
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
                        borderWidth: 1,
                      }]
                    },
                    options: {
                        borderColor: '#F9E400',
                        backgroundColor: '#C65BCF',
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
                      },
                      animation: {
                        duration: 2000,
                        easing: 'easeOutBounce', 
                        delay: (context) => context.dataIndex * 200, 
                        onProgress: (animation) => {
                            console.log('Animation Progress:', animation.currentStep / animation.numSteps);
                        },
                        onComplete: () => {
                            console.log('Animation Complete');
                        }
                    },
                    hover: {
                        animationDuration: 500,
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

function initEarningChart()
{
    axios.get(apiURL + `graph/getEarningGraph/${localStorage.getItem('userId')}`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log(response.data);

                new Chart(earningsChart, {
                    type: 'bar',
                    data: {
                      labels: response.data.date,
                      datasets: [{
                        label: 'Earnings',
                        data: response.data.sum,
                        borderWidth: 1
                      }]
                    },
                    options: {
                        borderColor: '#FFF100',
                        backgroundColor: '#874CCC',
                        legend: {
                            position: 'top',
                          },
                          title: {
                            display: true,
                            text: 'Earnings'
                          },
                      scales: {
                        y: {
                          beginAtZero: true
                        }
                      },

                      animation: {
                        duration: 2000,
                        easing: 'easeOutBounce', 
                        delay: (context) => context.dataIndex * 200, 
                        onProgress: (animation) => {
                            console.log('Animation Progress:', animation.currentStep / animation.numSteps);
                        },
                        onComplete: () => {
                            console.log('Animation Complete');
                        }
                    },
                    hover: {
                        animationDuration: 500,
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
                        label: 'Budget',
                        data: response.data.sum,
                        type: 'bar'
                      }
                    ],
                    labels: response.data.date,

                    },
                    options: {
                        borderColor: '#FFF100',
                        backgroundColor: '#7E60BF',
                         responsive: true,
                        legend: {
                            position: 'top',
                          },
                          title: {
                            display: true,
                            text: 'Budget'
                          },
                          animation: {
                            duration: 2000,
                            easing: 'easeOutBounce', 
                            delay: (context) => context.dataIndex * 200, 
                            onProgress: (animation) => {
                                console.log('Animation Progress:', animation.currentStep / animation.numSteps);
                            },
                            onComplete: () => {
                                console.log('Animation Complete');
                            }
                        },
                        hover: {
                            animationDuration: 500,
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