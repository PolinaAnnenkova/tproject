<template>
    <div id="app">
        <MainPageVue />
    </div>
</template>

<script>
    import MainPageVue from './components/MainPage.vue';
    import ProjectsList from './components/ProjectsList.vue';
    import TasksListVue from './components/TasksList.vue';

export default {
  name: 'App',
        components: {
            MainPageVue,
      ProjectsList,
      TasksListVue
  }
};
</script>

<style>
    /* Global styles (if any) */
</style>
