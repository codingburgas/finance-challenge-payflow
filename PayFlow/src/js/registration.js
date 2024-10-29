import axios from 'axios';
const apiURL = 'http://localhost:18080/api/'


document.getElementById('registerForm').addEventListener('submit', (event)=>{
    debugger;
    event.preventDefault();
    const formData = new FormData(event.target);
    const formJSON = Object.fromEntries(formData.entries());
    register(formJSON);
});


function register(body)
{
    axios.post(apiURL + `user/register`, body)
    .then(function (response) {
        if(response.status == 200)
        {
            if(response != null)
            {

                console.log(response.data);
                if(response.data.userId != -1)
                {
                    localStorage.setItem('userId', response.data.userId);
                    location.replace('html/dashboard.html');
                }
                else
                {
                    alert("Unauthorised");
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