import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'

document.addEventListener("DOMContentLoaded", (event) => {
    let userId = localStorage.getItem('userId'); 
    if(userId == -1 || userId == null || userId == undefined || userId == "undefined")
    {
        location.replace('../index.html');
    }
});

document.getElementById("earnings").addEventListener("click", function(event) {
    debugger;
    if (event.target && event.target.classList.contains("delete-btn")) {
        const earningItem = event.target.closest(".earning-item");
        if (earningItem) {
            const earningId = earningItem.getAttribute("data-id");
            deleteEarning(earningId);
        }
    }
});

document.getElementById('earningForm').addEventListener('submit', (event)=>{
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    getEarnings(formJSON.year, formJSON.month);
});

document.getElementById('addEarningForm').addEventListener('submit', (event)=>{
   event.preventDefault();
    debugger;
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    formJSON.userId = parseInt(localStorage.getItem('userId'));
    formJSON.date = `${formJSON.date} 00:00:00`;
    formJSON.id = parseInt(-1);
    formJSON.amount = parseInt(formJSON.amount);
    addEarnings(formJSON);
});

initData();

function initData()
{
    const currentDate = new Date();
    const currentYear = currentDate.getFullYear();
    const currentMonth = currentDate.getMonth() + 1;
    getEarnings(currentYear, currentMonth);
    getUserData();
}

function getEarnings(year, month)
{
    axios.get(apiURL + `earning/getByUser/${localStorage.getItem('userId')}/${year}/${month}`)
    .then(function (response) {
        if(response.status == 200)
        {
        debugger;
           const oldEarnings = document.querySelectorAll(".earning-item");
           oldEarnings.forEach(oldEarning => oldEarning.remove());
            if(response.data != null)
            {
                console.log(response.data);

                let earnings = response.data;
                for(let i = 0;i<earnings.length;i++)
                {
                    document.getElementById('earnings').innerHTML+=`
                        <div class="earning-item" data-id="${earnings[i].id}">
                            <div class="earning-info">
                                <div class="earning-icon"></div>
                                <span>${earnings[i].type}</span>
                            </div>
                                <span>${earnings[i].amount} $</span>
                            <div class="transaction-icon1">
                                <span>${earnings[i].date}</span>
                            </div>
                            <button class="delete-btn" type="button">Delete</button>
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

function addEarnings(body)
{
    axios.post(apiURL + 'earning/add', body)
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
                initData();
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
        debugger;
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

function deleteEarning(earningId)
{
    axios.delete(apiURL + `earning/delete/${earningId}`)
    .then(function (response) {
        debugger;
        if(response.status == 200)
        {
            if(response.data != null)
            {
                console.log('earning deleted');
                initData();
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