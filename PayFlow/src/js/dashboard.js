import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'

document.addEventListener("DOMContentLoaded", (event) => {
    debugger;
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

// function getExpenses()
// {
//     axios.get(apiURL + `expense/getFixedByUser/${localStorage.getItem('userId')}/7`)
//     .then(function (response) {
//         if(response.status == 200)
//         {
//             if(response.data != null)
//             {
//                 console.log(response.data);

//                 let expenses = response.data;
    
//                 for(let i = 0;i<expenses.length;i++)
//                 {
//                     document.getElementById('expenses-card').innerHTML+=`
//                         <div class="transaction">
//                             <div class="transaction-info">
//                                 <div class="transaction-icon"></div>
//                                 <span>${expenses[i].type}</span>
//                             </div>
//                             <span>${expenses[i].amount} $</span>
//                         </div>
//                     `;
//                 }
//             }
//         }
//         else
//         {
//             console.log(error);
//             alert("Unauthorised");
//         }
//     })
//     .catch(function (error) {
//         console.log(error);
//         alert("Fatal error");
//     });
// }

// function getEarnings(){
//     axios.get(apiURL + `earning/getFixedByUser/${localStorage.getItem('userId')}/7`)
//     .then(function (response) {
//         if(response.status == 200)
//         {
//             if(response.data != null)
//             {
//                 console.log(response.data);

//                 let earnings = response.data;
    
//                 for(let i = 0;i<earnings.length;i++)
//                 {
//                     document.getElementById('earnings-card').innerHTML+=`
//                         <div class="transaction">
//                             <div class="transaction-info">
//                                 <div class="transaction-icon"></div>
//                                 <span>${earnings[i].type}</span>
//                             </div>
//                             <span>${earnings[i].amount} $</span>
//                         </div>
//                     `;
//                 }
//             }
//         }
//         else
//         {
//             console.log(error);
//             alert("Unauthorised");
//         }
//     })
//     .catch(function (error) {
//         console.log(error);
//         alert("Fatal error");
//     });
// }