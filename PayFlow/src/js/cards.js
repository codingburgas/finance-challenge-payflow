import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'

initData();

function initData()
{
    getExpenses();
    getUserData();
}

function getExpenses()
{
    axios.get(apiURL + `expense/getFixedByUser/${localStorage.getItem('userId')}/7`)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log(response.data);

                let expenses = response.data;
    
                for(let i = 0;i<expenses.length;i++)
                {
                    document.getElementById('expenses').innerHTML+=`
                        <div class="expense-item">
                            <div class="expense-info">
                                <div class="expense-icon"></div>
                                <span>${expenses[i].type}</span>
                            </div>
                            <span>${expenses[i].amount} $</span>
                        </div>
                    `;
                }
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

