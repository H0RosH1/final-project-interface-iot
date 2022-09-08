$("#auto-id").on('click', ()=>{
    if($("#auto-id").is(':checked')) {
        $('#id').prop('disabled',true);
        location.reload();
    }else{
        $('#id').prop('disabled',false);
    }
})

$("#type").change(function () {
    let type_chicken = $("#type").val()
    if(type_chicken == "ไก่เด็ก"){
        $('.format-sex').css('display', 'none');
        $('.format-sexing').css('display', 'flex');
        
        $('.img').attr('src','./img/chick.png');
        $('#sex').prop('required',false)
        $('#sexing').prop('required',true)
    }else{
        $('.format-sexing').css('display', 'none');
        $('.format-sex').css('display', 'flex');
        $('#sex').prop('required',true)
        $('#sexing').prop('required',false)
        if(type_chicken == "ไก่รุ่น"){
            $('.img').attr('src','./img/chickyung.png');
        }
        if(type_chicken == "ไก่หนุ่ม" || type_chicken == "ไก่สาว"){
            $('.img').attr('src','./img/chickboy.png');
        }
        if(type_chicken == "ไก่ทดแทน"){
            $('.img').attr('src','./img/chicken_sup.png');
        }
        if(type_chicken == "ไก่พ่อแม่พันธุ์"){
            $('.img').attr('src','./img/img_chicken.png');
        }
    }
})