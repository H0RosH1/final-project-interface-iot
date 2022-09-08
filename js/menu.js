$(".sidebar").on('click', () => {
    $(".sidebar").toggleClass("active");
})

$("#btn").on('click', () => {
    $(".sidebar").toggleClass("active");
})

$(".nav_list").on('click', () => {
    $(".sidebar").toggleClass("active");
})

$('body').on('click',function(event){
    if(!$(event.target).is('.sidebar') && !$(event.target).is('#btn')){
      $(".sidebar").removeClass("active");
    }
});

$('.add_chicken').on('click', () => {
    $(".popup").show();
})
$('.bxs-x-circle').on('click', () => {
    $(".popup").hide();
})
$('input:radio[name="layout"]').change(function () {
    $(".chicken_box").toggleClass("list");
});
$('input:radio[name="layout_sup"]').change(function () {
    $(".chicken_box").toggleClass("list");
});

$('input:radio[name="layout"]').change(function () {
    $(".contain_chicken").toggleClass("list");
});

