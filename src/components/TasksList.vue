<template>
    <div>

        <div class="flex bg-blue-100">

            <main class="flex-1 p-4">

                <div v-if="currentTab === 'tasks'">
                    <h2 class="text-2xl mb-4">Список задач</h2>
                    <button @click="currentTab = 'addTask'"
                            :class="{'text-blue-500': currentTab === 'addTask', 'bg-blue-300 text-white': currentTab !== 'addTask'}"
                            class="px-4 py-2 rounded mb-2">
                        Добавить задачу
                    </button>

                    <table class="min-w-full bg-white">
                        <thead class="bg-blue-300">
                            <tr>
                                <th class="text-white w-1/3 px-4 py-2">Название задачи</th>
                                <th class="text-white w-1/6 px-4 py-2">Проект</th>
                                <th class="text-white w-1/6 px-4 py-2">Активный</th>
                                <th class="text-white w-1/6 px-4 py-2">Проводки</th>
                                <th class="text-white w-1/3 px-4 py-2 text-center">Действия</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="(task, index) in tasks" :key="task.name" class="border-t">
                                <td class="text-center px-4 py-2">{{ task.name }}</td>
                                <td class="text-center px-4 py-2">{{ task.name_project }}</td>
                                <td class="text-center px-4 py-2">{{ task.active ? 'Да' : 'Нет' }}</td>
                                <td class="text-center px-4 py-2">
    <li v-for="t in task.time">{{ t.date }} {{t.hour  }}</li> </td>
    <td class="px-4 py-2 text-center">
        <button @click="editTask(index)" class="text-blue-500 mr-2">✏️</button>
        <button @click="deleteTask(index)" class="text-red-500 mr-2">🗑️</button>
        <button @click="saveTask(index)" class="text-green-500">💾</button>
    </td>
    </tr>

    </tbody>
    </table>
    </div>
    <div v-if="currentTab === 'addTask'">
        <h2 class="text-2xl mb-4">Добавление задачи</h2>
        <ul>
            <TextElement label="Label" :columns="{ container: 12, label: 4, wrapper: 12 }" />
            <TextElement label="Label" :columns="{ container: 12, label: 4, wrapper: 6 }" />
        </ul>
    </div>
    </main>
    </div>
    </div>
</template>

<script>
  export default {
    data() {
      return {
          currentTab: 'tasks',

        tasks: [
            { name: 'Название1', name_project: 'Проект1', active: true, time: [{ date: '01.01.2024', hour: '02:30' }, { date: '02.01.2024', hour: '08:30' }] },
            { name: 'Название2', name_project: 'Проект1', active: true, time: [] },
            { name: 'Название3', name_project: 'Проект2', active: true, time: [{ date: '05.05.2024', hour: '02:14' }] },
            { name: 'Название4', name_project: 'Проект3', active: false, time: [{ date: '06.06.2024', hour: '06:45' }, { date: '07.06.2024', hour: '03:25' }]},
            { name: 'Название5', name_project: 'Проект3', active: true, time: [{ date: '08.06.2024', hour: '01:10' }]},
        ],
          newTask: { name: '', name_project: '', active: false, time: []}
      };
    },
    methods: {
        addTask() {
            if (this.newTask.name && this.newTask.code) {
          this.projects.push({ ...this.newProject });
                this.newProject = { name: '', name_project: '', active: false, time: [] };
        }
      },
        editTask(index) {
            this.newTask = { ...this.tasks[index] };
            this.tasks.splice(index, 1);
      },
        deleteTask(index) {
            this.tasks.splice(index, 1);
      },
        saveTask(index) {
            this.tasks.splice(index, 1, this.newTask);
            this.newProject = { name: '', name_project: '', active: false, time: [] };
      }
    }
  };
</script>

<style scoped>
    /* Add any additional styles here */
</style>
