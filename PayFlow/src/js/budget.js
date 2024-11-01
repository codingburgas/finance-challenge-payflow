import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'

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
    getBudgets();
}

document.getElementById('addBudgetForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    formJSON.userId = parseInt(localStorage.getItem('userId'));
    formJSON.id = parseInt(-1);
    formJSON.amount = parseInt(formJSON.amount);
    addBudget(formJSON);
});


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

function getBudgets()
{
     axios.get(apiURL + `budget/getByUser/${localStorage.getItem('userId')}`)
     .then(function (response) {
        if(response.status == 200)
         {
            
            const oldEarnings = document.querySelectorAll(".budget-item");
            oldEarnings.forEach(oldEarning => oldEarning.remove());
             if(response.data != null)
             {
                 console.log(response.data);

                 let budgets = response.data;
    
                 for(let i = 0;i<budgets.length;i++)
                 {
                     document.getElementById('budgets').innerHTML+=`
                         <div class="budget-item">
                            <div class="budget-info">
                                <div class="budget-icon"></div>
                                <span>${budgets[i].expenseType}</span>
                            </div>
                            <span>${budgets[i].amount} $</span>
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

function addBudget(body)
{
    axios.post(apiURL + 'budget/add', body)
    .then(function (response) {
        if(response.status == 200 || response.status == 204)
        {
            if(response != null)
            {
                console.log(response.data);
                if(response.data.userId != -1)
                {
                    document.getElementById('successMessage').innerText;
                }
                else
                {
                    alert("Unauthorised");
                }
                getBudgets();
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